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

inline constexpr BNotControl kBNotControl;
inline constexpr BControlPlayer kBControlPlayer;

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

inline constexpr BNotGetGravity kBNotGetGravity;
inline constexpr BGetGravity kBGetGravity;

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

inline constexpr BNotGetAirDrag kBNotGetAirDrag;
inline constexpr BGetLinearAirDrag kBGetLinearAirDrag;

class BUpdateABehavior {
public:
    virtual void UpdateA(EResource& self) const = 0;
};

class BNotUpdateA : public BUpdateABehavior {
public:
    void UpdateA(EResource& self) const override { /* NO-OP */ }
};

class BAddForceToA : public BUpdateABehavior {
public:
    void UpdateA(EResource& self) const override;
};

inline constexpr BNotUpdateA kBNotUpdateA;
inline constexpr BAddForceToA kBAddForceToA;

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
    Entity(EResource res,
           const BControlBehavior& control,
           const BGetGravityBehavior& get_gravity,
           const BGetAirDragBehavior& get_air_drag,
           const BUpdateABehavior& update_a,
           const BUpdateBehavior& update)
        : res_(res),
          control_(control),
          get_gravity_(get_gravity),
          get_air_drag_(get_air_drag),
          update_a_(update_a),
          update_(update) {}
    ~Entity() {}

    const EResource& res() { return res_; }

    void Control(const KeyboardHandler& kbd_handler);
    void GetGravity(const Vector2D& g);
    void GetAirDrag();
    void UpdateA();
    void Update();

private:
    EResource res_;

    const BControlBehavior& control_;
    const BGetGravityBehavior& get_gravity_;
    const BGetAirDragBehavior& get_air_drag_;
    const BUpdateABehavior& update_a_;
    const BUpdateBehavior& update_;
};

#endif  // RUMRAISIN_MODELS_ENTITY_H_
