#include "models/entity.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include "interfaces/config.h"
#include "interfaces/keyboard.h"
#include "models/field.h"

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

bool CollideWithGridsBelow(
        EResource& res, const Field& field, int row, int col) {
    /*
    bool collides = false;
    switch (field.GetCollision(row, col).coll_id) {
    case TileCollisionId::kNone:
        break;
    case TileCollisionId::kSolid: {
        int anchor_y = res.r.y + res.height;
        int floor_y = kGridUnit * row;
        if ((anchor_y <= floor_y) && (floor_y <= anchor_y + res.v.y)) {
            res.v.y = floor_y - anchor_y;
        }
        break;
    }
    default:
        break;
    }
    return collides;
    */
}

void MeetGridsBelow(EResource& res, const Field& field) {
    /*
    assert(res.v.y > 0.0f);
    float anchor_y = res.r.y + res.height;
    int s_row = static_cast<int>(std::floor(anchor_y / kGridUnit));
    int e_row = static_cast<int>(std::floor((anchor_y + res.v.y) / kGridUnit));
    int s_col, e_col;
    float k1, k2;
    bool collides;
    for (int i = s_row; i <= e_row; ++i) {
        k1 = std::clamp(kGridUnit*(i + 1) - anchor_y, 0.0f, res.v.y);
        k2 = std::clamp(kGridUnit*i - anchor_y, 0.0f, res.v.y);
        if (res.v.x < 0.0f) {
            s_col = static_cast<int>(
                std::floor((res.r.x + k1/res.v.y*res.v.x) / kGridUnit));
            e_col = static_cast<int>(
                std::floor(
                    (res.r.x + k2/res.v.y*res.v.x + res.width)
                    / kGridUnit));
        } else {
            s_col = static_cast<int>(
                std::floor((res.r.x + k2/res.v.y*res.v.x) / kGridUnit));
            e_col = static_cast<int>(
                std::floor(
                    (res.r.x + k1/res.v.y*res.v.x + res.width)
                    / kGridUnit));
        }
        for (int j = s_col; j <= e_col; ++j) {
            collides = CollideWithGridsBelow(res, field, i, j);
            if (res.v.y <= 0.0f) {
                break;
            }
        }
        if (collides) {
            break;
        }
    }
    */
}

}  // namespace

void BMeetField::MeetField(EResource& self, const Field& field) const {
    // TODO: Implement this!
    if (self.v.y < 0.0f) {
        // ...
    } else if (self.v.y > 0.0f) {
        MeetGridsBelow(self, field);
    }
}

void BDetectCollision::DetectCollision(
        EResource& self, const BMeetFieldBehavior& meet_field,
        const Field& field) const {
    // TODO: Implement this!
    if (self.v.y < 0.0f) {
        //
    } else if (self.v.y > 0.0f) {
        //
    }
    if (self.v.x < 0.0f) {
        //
    } else if (self.v.x > 0.0f) {
        //
    }
}

void BAddVToR::UpdateR(EResource& self) const {
    self.r += self.v;
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
