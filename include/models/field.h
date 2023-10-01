#ifndef RUMRAISIN_MODELS_FIELD_H_
#define RUMRAISIN_MODELS_FIELD_H_

#include <array>

#include "models/tile.h"

inline constexpr int kFieldMaxWidth = 100;
inline constexpr int kFieldMaxHeight = 100;

class Field {
public:
    Field() {}
    ~Field() {}

    void Load();

    const Tile& GetCollision(int row, int col) const;

private:
    std::array<
        std::array<unsigned int, kFieldMaxWidth>,
        kFieldMaxHeight> collision_;
};

#endif  // RUMRAISIN_MODELS_FIELD_H_
