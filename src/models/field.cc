#include "models/field.h"

void Field::Load() {
    // just for debugging
    for (int i = 0; i < kFieldMaxHeight; ++i) {
        for (int j = 0; j < kFieldMaxWidth; ++j) {
            collision_[i][j] = 0;
        }
    }
}
