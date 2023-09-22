#include <iostream>

#include "models/general.h"

void PrintVector2D(const char* label, const Vector2D& vec) {
    std::cout << label << "  x: " << vec.x << ", y: " << vec.y << std::endl;
}

int main() {
    Vector2D zero_vec;
    PrintVector2D("zero_vec", zero_vec);

    Vector2D vec_1 = {2.1f, 5.7f};
    Vector2D vec_2(3.3f, -0.5f);
    PrintVector2D("vec_1", vec_1);
    PrintVector2D("vec_2", vec_2);

    vec_1.SetToZeros();
    PrintVector2D("set vec_1 to zeros", vec_1);

    vec_1.Set(-2.3f, 5.4f);
    PrintVector2D("set vec_1 to (-2.3, 5.4)", vec_1);

    return 0;
}
