#ifndef RUMRAISIN_INTERFACES_KEYBOARD_H_
#define RUMRAISIN_INTERFACES_KEYBOARD_H_

#include <array>

enum class KeyCode {
    kUp,
    kLeft,
    kRight,
    kDown,
    kMax
};

inline constexpr int kNumberOfKeyCodes = static_cast<int>(KeyCode::kMax);

class KeyboardHandler {
public:
    KeyboardHandler() {
        for (int i = 0; i < kNumberOfKeyCodes; ++i) {
            is_pressed_[i] = false;
            is_pressed_previously_[i] = false;
        }
    }
    ~KeyboardHandler() {}

private:
    std::array<bool, kNumberOfKeyCodes> is_pressed_;
    std::array<bool, kNumberOfKeyCodes> is_pressed_previously_;
};

#endif  // RUMRAISIN_INTERFACES_KEYBOARD_H_
