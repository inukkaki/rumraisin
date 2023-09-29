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

class BUpdateBehavior {
public:
    virtual void Update(EResource& self) const = 0;
};

class BNotUpdate : public BUpdateBehavior {
public:
    void Update(EResource& self) const override { /* NO-OP */ }
};

class BUpdate : public BUpdateBehavior {
public:
    void Update(EResource& self) const override;
};

inline constexpr BNotUpdate kBNotUpdate;
inline constexpr BUpdate kBUpdate;

class Entity {
public:
    explicit Entity(const BUpdateBehavior& update) : update_(update) {}
    ~Entity() {}

    // just for debugging
    EResource& res() { return res_; }

    void Update();

private:
    EResource res_;

    const BUpdateBehavior& update_;
};

#endif  // RUMRAISIN_MODELS_ENTITY_H_
