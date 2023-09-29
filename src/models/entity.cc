#include "models/entity.h"

void BGetGravity::GetGravity(EResource& self, const Vector2D& g) const {
    self.external_force += self.mass * g;
}

void BUpdate::Update(EResource& self) const {
    self.a = self.external_force / self.mass;
    self.external_force.SetToZeros();
    self.v += self.a;
    self.r += self.v;
}

void Entity::GetGravity(const Vector2D& g) {
    get_gravity_.GetGravity(res_, g);
}

void Entity::Update() {
    update_.Update(res_);
}
