#include "models/general.h"

void Vector2D::SetToZeros() {
    x = 0.0f;
    y = 0.0f;
}

void Vector2D::Set(float u, float v) {
    x = u;
    y = v;
}

Vector2D operator+(const Vector2D& v) {
    Vector2D tmp(+v.x, +v.y);
    return tmp;
}

Vector2D operator-(const Vector2D& v) {
    Vector2D tmp(-v.x, -v.y);
    return tmp;
}
