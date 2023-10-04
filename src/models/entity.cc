#include "models/entity.h"

#include "interfaces/keyboard.h"

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

void BAddVToR::UpdateR(EResource& self) const {
    self.r += self.v;
}

void BUpdate::Update(EResource& self) const {
    self.a = self.external_force / self.mass;
    self.external_force.SetToZeros();
    self.v += self.a;
    self.r += self.v;
}

void Entity::Control(const KeyboardHandler& kbd_handler) {
    control_.Control(res_, kbd_handler);
}

void Entity::GetGravity(const Vector2D& g) {
    get_gravity_.GetGravity(res_, g);
}

void Entity::GetAirDrag() {
    get_air_drag_.GetAirDrag(res_);
}

void Entity::UpdateA() {
    update_a_.UpdateA(res_);
}

void Entity::UpdateV() {
    update_v_.UpdateV(res_);
}

void Entity::UpdateR() {
    update_r_.UpdateR(res_);
}

void Entity::Update() {
    update_.Update(res_);
}
