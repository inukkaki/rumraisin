#ifndef RUMRAISIN_MODELS_ENTITY_H_
#define RUMRAISIN_MODELS_ENTITY_H_

#include "models/general.h"

struct EResource {
    float width;   // px
    float height;  // px

    Vector2D r;  // px
    Vector2D v;  // px frame-1
    Vector2D a;  // px frame-2
};

class Entity {
public:
    Entity() {}
    ~Entity() {}

    // just for debugging
    EResource& res() { return res_; }

private:
    EResource res_;
};

#endif  // RUMRAISIN_MODELS_ENTITY_H_
