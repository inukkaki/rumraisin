#ifndef RUMRAISIN_MODELS_FIELD_H_
#define RUMRAISIN_MODELS_FIELD_H_

#include <array>

inline constexpr int kFieldMaxWidth = 100;
inline constexpr int kFieldMaxHeight = 100;

class Field {
public:
    Field() {}
    ~Field() {}

private:
    std::array<
        std::array<unsigned int, kFieldMaxWidth>,
        kFieldMaxHeight> collision_;
};

#endif  // RUMRAISIN_MODELS_FIELD_H_
