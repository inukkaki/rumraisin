#ifndef RUMRAISIN_MODELS_GENERAL_H_
#define RUMRAISIN_MODELS_GENERAL_H_

struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float u, float v) : x(u), y(v) {}
    ~Vector2D() {}

    void SetToZeros();
    void Set(float u, float v);
};

Vector2D operator+(const Vector2D& v);
Vector2D operator-(const Vector2D& v);

#endif  // RUMRAISIN_MODELS_GENERAL_H_
