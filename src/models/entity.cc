#include "models/entity.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include "interfaces/config.h"
#include "interfaces/keyboard.h"
#include "models/field.h"
#include "models/general.h"

void BControlPlayer::Control(
        EResource& self, const KeyboardHandler& kbd_handler) const {
    // just for debugging
    if (kbd_handler.Pressing(KeyCode::kLeft)) {
        self.external_force += Vector2D(-0.75f, 0.0f);
    }
    if (kbd_handler.Pressing(KeyCode::kRight)) {
        self.external_force += Vector2D(0.75f, 0.0f);
    }
    if (self.r.y > 340.0f) {
        self.r.y = -20.0f;
    }
}

void BGetGravity::GetGravity(EResource& self, const Vector2D& g) const {
    self.external_force += self.mass * g;
}

void BGetLinearAirDrag::GetAirDrag(EResource& self) const {
    self.external_force -= self.air_drag_coefficient * self.v;
}

void BAddForceToA::UpdateA(EResource& self) const {
    self.a = self.external_force / self.mass;
    self.external_force.SetToZeros();
}

void BAddAToV::UpdateV(EResource& self) const {
    self.v += self.a;
}

namespace {

bool CollideRightward(EResource& res, float border_x) {
    assert(res.v.x > 0.0f);
    bool collides = false;
    float anchor_x = res.r.x + res.width;
    if ((anchor_x <= border_x) && (border_x <= anchor_x + res.v.x)) {
        collides = true;
        res.v.x = border_x - anchor_x;
    }
    return collides;
}

bool CollideDownward(EResource& res, float border_y) {
    assert(res.v.y > 0.0f);
    bool collides = false;
    float anchor_y = res.r.y + res.height;
    if ((anchor_y <= border_y) && (border_y <= anchor_y + res.v.y)) {
        collides = true;
        res.v.y = border_y - anchor_y;
        res.is_aligned_d = true;
        res.aligned_y = border_y - res.height;
    }
    return collides;
}

}  // namespace

bool BMeetField::MeetField(
        EResource& self, const Field& field, Direction direction,
        int row, int col) const {
    // TODO: Implement this!
    bool collides = false;
    const Tile& tile = field.GetCollision(row, col);
    switch (direction) {
    case Direction::kUp:
        // ...
        break;
    case Direction::kLeft:
        // ...
        break;
    case Direction::kRight:
        if (tile.is_close_l) {
            collides = CollideRightward(self, kGridUnit * col);
        }
        break;
    case Direction::kDown:
        if (tile.is_close_t) {
            collides = CollideDownward(self, kGridUnit * row);
        }
        break;
    default:
        break;
    }
    // just for debugging
    IncrementFieldReferenceCount(row, col);
    return collides;
}

namespace {

void DetectCollisionDownward(
        EResource& res, const BMeetFieldBehavior& meet_field,
        const Field& field) {
    assert(res.v.y > 0.0f);
    float anchor_y = res.r.y + res.height;
    int s_row = static_cast<int>(std::floor(anchor_y / kGridUnit));
    int e_row = static_cast<int>(std::floor((anchor_y + res.v.y) / kGridUnit));
    float k1, k2;
    int s_col, e_col;
    bool collides = false;
    for (int i = s_row; i <= e_row; ++i) {
        k1 = std::clamp(kGridUnit*(i + 1) - anchor_y, 0.0f, res.v.y) / res.v.y;
        k2 = std::clamp(kGridUnit*i - anchor_y, 0.0f, res.v.y) / res.v.y;
        if (res.v.x < 0.0f) {
            s_col = static_cast<int>(
                std::floor((res.r.x + k1*res.v.x) / kGridUnit)
            );
            e_col = static_cast<int>(
                std::floor((res.r.x + k2*res.v.x + res.width - 1) / kGridUnit)
            );
        } else {
            s_col = static_cast<int>(
                std::floor((res.r.x + k2*res.v.x) / kGridUnit)
            );
            e_col = static_cast<int>(
                std::floor((res.r.x + k1*res.v.x + res.width - 1) / kGridUnit)
            );
        }
        for (int j = s_col; j <= e_col; ++j) {
            collides = meet_field.MeetField(
                res, field, Direction::kDown, i, j);
            if (collides) {
                break;
            }
        }
        if (collides) {
            break;
        }
    }
}

void DetectCollisionRightward(
        EResource& res, const BMeetFieldBehavior& meet_field,
        const Field& field) {
    assert(res.v.x > 0.0f);
    float anchor_x = res.r.x + res.width;
    int s_col = static_cast<int>(std::floor(anchor_x / kGridUnit));
    int e_col = static_cast<int>(std::floor((anchor_x + res.v.x) / kGridUnit));
    float k1, k2;
    int s_row, e_row;
    bool collides = false;
    for (int j = s_col; j <= e_col; ++j) {
        k1 = std::clamp(kGridUnit*(j + 1) - anchor_x, 0.0f, res.v.x) / res.v.x;
        k2 = std::clamp(kGridUnit*j - anchor_x, 0.0f, res.v.x) / res.v.x;
        if (res.v.y < 0.0f) {
            s_row = static_cast<int>(
                std::floor((res.r.y + k1*res.v.y) / kGridUnit)
            );
            e_row = static_cast<int>(
                std::floor((res.r.y + k2*res.v.y + res.height - 1) / kGridUnit)
            );
        } else {
            s_row = static_cast<int>(
                std::floor((res.r.y + k2*res.v.y) / kGridUnit)
            );
            e_row = static_cast<int>(
                std::floor((res.r.y + k1*res.v.y + res.height - 1) / kGridUnit)
            );
        }
        for (int i = s_row; i <= e_row; ++i) {
            collides = meet_field.MeetField(
                res, field, Direction::kRight, i, j);
            if (collides) {
                break;
            }
        }
        if (collides) {
            break;
        }
    }
}

}  // namespace

void BDetectCollision::DetectCollision(
        EResource& self, const BMeetFieldBehavior& meet_field,
        const Field& field) const {
    // TODO: Implement this!
    if (self.v.y < 0.0f) {
        //
    } else if (self.v.y > 0.0f) {
        DetectCollisionDownward(self, meet_field, field);
    }
    if (self.v.x < 0.0f) {
        //
    } else if (self.v.x > 0.0f) {
        DetectCollisionRightward(self, meet_field, field);
    }
}

void BAddVToR::UpdateR(EResource& self) const {
    self.r += self.v;
}

void BAddVToRWithAligning::UpdateR(EResource& self) const {
    self.r += self.v;
    if (self.is_aligned_d) {
        self.r.y = self.aligned_y;
        self.is_aligned_d = false;
    }
}

void Entity::Control(const KeyboardHandler& kbd_handler) {
    control_->Control(res_, kbd_handler);
}

void Entity::GetGravity(const Vector2D& g) {
    get_gravity_->GetGravity(res_, g);
}

void Entity::GetAirDrag() {
    get_air_drag_->GetAirDrag(res_);
}

void Entity::UpdateA() {
    update_a_->UpdateA(res_);
}

void Entity::UpdateV() {
    update_v_->UpdateV(res_);
}

void Entity::DetectCollision(const Field& field) {
    detect_collision_->DetectCollision(res_, *meet_field_, field);
}

void Entity::UpdateR() {
    update_r_->UpdateR(res_);
}
