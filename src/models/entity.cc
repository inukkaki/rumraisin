#include "models/entity.h"

void BUpdate::Update(EResource& self) const {
    // just for debugging
    self.v += self.a;
    self.r += self.v;
}

void Entity::Update() {
    update_.Update(res_);
}
