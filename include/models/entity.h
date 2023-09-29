#ifndef RUMRAISIN_MODELS_ENTITY_H_
#define RUMRAISIN_MODELS_ENTITY_H_

#include "models/general.h"

struct EResource {
    float width;   // px
    float height;  // px

    Vector2D r;  // px
    Vector2D v;  // px frame-1
    Vector2D a;  // px frame-2

    float mass;  // kg
    Vector2D external_force;  // kg px frame-2
};

class BGetGravityBehavior {
public:
    virtual void GetGravity(EResource& self, const Vector2D& g) const = 0;
};

class BNotGetGravity : public BGetGravityBehavior {
public:
    void GetGravity(EResource& self, const Vector2D& g) const override {
        /* NO-OP */
    }
};

class BGetGravity : public BGetGravityBehavior {
public:
    void GetGravity(EResource& self, const Vector2D& g) const override;
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

inline constexpr BNotGetGravity kBNotGetGravity;
inline constexpr BGetGravity kBGetGravity;

inline constexpr BNotUpdate kBNotUpdate;
inline constexpr BUpdate kBUpdate;

class Entity {
public:
    Entity(const BGetGravityBehavior& get_gravity,
           const BUpdateBehavior& update)
        : get_gravity_(get_gravity),
          update_(update) {}
    ~Entity() {}

    // just for debugging
    EResource& res() { return res_; }

    void GetGravity(const Vector2D& g);
    void Update();

private:
    EResource res_;

    const BGetGravityBehavior& get_gravity_;
    const BUpdateBehavior& update_;
};

#endif  // RUMRAISIN_MODELS_ENTITY_H_
