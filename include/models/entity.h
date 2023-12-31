#ifndef RUMRAISIN_MODELS_ENTITY_H_
#define RUMRAISIN_MODELS_ENTITY_H_

#include "interfaces/keyboard.h"
#include "models/field.h"
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

    bool is_aligned_l;  // On the left side
    bool is_aligned_r;  // On the right side
    bool is_aligned_d;  // On the down-side

    float aligned_x;
    float aligned_y;
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

class BUpdateVBehavior {
public:
    virtual void UpdateV(EResource& self) const = 0;
};

class BNotUpdateV : public BUpdateVBehavior {
public:
    void UpdateV(EResource& self) const override { /* NO-OP */ }
};

class BAddAToV : public BUpdateVBehavior {
public:
    void UpdateV(EResource& self) const override;
};

inline constexpr BNotUpdateV kBNotUpdateV;
inline constexpr BAddAToV kBAddAToV;

class BMeetFieldBehavior {
public:
    virtual bool MeetField(
            EResource& self, const Field& field, Direction direction,
            int row, int col) const = 0;
};

class BNotMeetField : public BMeetFieldBehavior {
public:
    bool MeetField(
            EResource& self, const Field& field, Direction direction,
            int row, int col) const override {
        return false;
    }
};

class BMeetField : public BMeetFieldBehavior {
public:
    bool MeetField(
            EResource& self, const Field& field, Direction direction,
            int row, int col) const override;
};

inline constexpr BNotMeetField kBNotMeetField;
inline constexpr BMeetField kBMeetField;

class BDetectCollisionBehavior {
public:
    virtual void DetectCollision(
            EResource& self, const BMeetFieldBehavior& meet_field,
            const Field& field) const = 0;
};

class BNotDetectCollision : public BDetectCollisionBehavior {
public:
    void DetectCollision(
            EResource& self, const BMeetFieldBehavior& meet_field,
            const Field& field) const override {
        /* NO-OP */
    }
};

class BDetectCollision : public BDetectCollisionBehavior {
public:
    void DetectCollision(
            EResource& self, const BMeetFieldBehavior& meet_field,
            const Field& field) const override;
};

inline constexpr BNotDetectCollision kBNotDetectCollision;
inline constexpr BDetectCollision kBDetectCollision;

class BUpdateRBehavior {
public:
    virtual void UpdateR(EResource& self) const = 0;
};

class BNotUpdateR : public BUpdateRBehavior {
public:
    void UpdateR(EResource& self) const override { /* NO-OP */ }
};

class BAddVToR : public BUpdateRBehavior {
public:
    void UpdateR(EResource& self) const override;
};

class BAddVToRWithAligning : public BUpdateRBehavior {
public:
    void UpdateR(EResource& self) const override;
};

inline constexpr BNotUpdateR kBNotUpdateR;
inline constexpr BAddVToR kBAddVToR;
inline constexpr BAddVToRWithAligning kBAddVToRWithAligning;

class Entity {
public:
    Entity(EResource res,
           const BControlBehavior& control,
           const BGetGravityBehavior& get_gravity,
           const BGetAirDragBehavior& get_air_drag,
           const BUpdateABehavior& update_a,
           const BUpdateVBehavior& update_v,
           const BMeetFieldBehavior& meet_field,
           const BDetectCollisionBehavior& detect_collision,
           const BUpdateRBehavior& update_r)
        : res_(res),
          control_(&control),
          get_gravity_(&get_gravity),
          get_air_drag_(&get_air_drag),
          update_a_(&update_a),
          update_v_(&update_v),
          meet_field_(&meet_field),
          detect_collision_(&detect_collision),
          update_r_(&update_r) {}
    ~Entity() {}

    const EResource& res() { return res_; }

    void Control(const KeyboardHandler& kbd_handler);
    void GetGravity(const Vector2D& g);
    void GetAirDrag();
    void UpdateA();
    void UpdateV();
    void DetectCollision(const Field& field);
    void UpdateR();

private:
    EResource res_;

    const BControlBehavior* control_;
    const BGetGravityBehavior* get_gravity_;
    const BGetAirDragBehavior* get_air_drag_;
    const BUpdateABehavior* update_a_;
    const BUpdateVBehavior* update_v_;
    const BMeetFieldBehavior* meet_field_;
    const BDetectCollisionBehavior* detect_collision_;
    const BUpdateRBehavior* update_r_;
};

#endif  // RUMRAISIN_MODELS_ENTITY_H_
