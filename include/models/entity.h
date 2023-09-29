#ifndef RUMRAISIN_MODELS_ENTITY_H_
#define RUMRAISIN_MODELS_ENTITY_H_

#include "interfaces/keyboard.h"
#include "models/general.h"

struct EResource {
    float width;   // px
    float height;  // px

    Vector2D r;  // px
    Vector2D v;  // px frame-1
    Vector2D a;  // px frame-2

    float mass;  // kg
    Vector2D external_force;  // kg px frame-2

    float air_drag_coefficient;
};

class BControlBehavior {
public:
    virtual void Control(
            EResource& self, const KeyboardHandler& kbd_handler) const = 0;
};

class BNotControl : public BControlBehavior {
public:
    void Control(EResource& self,
                 const KeyboardHandler& kbd_handler) const override {
        /* NO-OP */
    }
};

class BControlPlayer : public BControlBehavior {
public:
    void Control(EResource& self,
                 const KeyboardHandler& kbd_handler) const override;
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

class BGetAirDragBehavior {
public:
    virtual void GetAirDrag(EResource& self) const = 0;
};

class BNotGetAirDrag : public BGetAirDragBehavior {
public:
    void GetAirDrag(EResource& self) const override { /* NO-OP */ }
};

class BGetLinearAirDrag : public BGetAirDragBehavior {
public:
    void GetAirDrag(EResource& self) const override;
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

inline constexpr BNotControl kBNotControl;
inline constexpr BControlPlayer kBControlPlayer;

inline constexpr BNotGetGravity kBNotGetGravity;
inline constexpr BGetGravity kBGetGravity;

inline constexpr BNotGetAirDrag kBNotGetAirDrag;
inline constexpr BGetLinearAirDrag kBGetLinearAirDrag;

inline constexpr BNotUpdate kBNotUpdate;
inline constexpr BUpdate kBUpdate;

class Entity {
public:
    Entity(EResource res,
           const BControlBehavior& control,
           const BGetGravityBehavior& get_gravity,
           const BGetAirDragBehavior& get_air_drag,
           const BUpdateBehavior& update)
        : res_(res),
          control_(control),
          get_gravity_(get_gravity),
          get_air_drag_(get_air_drag),
          update_(update) {}
    ~Entity() {}

    const EResource& res() { return res_; }

    void Control(const KeyboardHandler& kbd_handler);
    void GetGravity(const Vector2D& g);
    void GetAirDrag();
    void Update();

private:
    EResource res_;

    const BControlBehavior& control_;
    const BGetGravityBehavior& get_gravity_;
    const BGetAirDragBehavior& get_air_drag_;
    const BUpdateBehavior& update_;
};

#endif  // RUMRAISIN_MODELS_ENTITY_H_
