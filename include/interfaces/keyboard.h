#ifndef RUMRAISIN_INTERFACES_KEYBOARD_H_
#define RUMRAISIN_INTERFACES_KEYBOARD_H_

#include <array>
#include <unordered_map>

#include "SDL2/SDL.h"

enum class KeyCode {
    kUp,
    kLeft,
    kRight,
    kDown,
    kMax
};

inline constexpr int kNumberOfKeyCodes = static_cast<int>(KeyCode::kMax);

void SetKeyMap(std::unordered_map<SDL_KeyCode, int>& key_map);

class KeyboardHandler {
public:
    KeyboardHandler() {
        SetKeyMap(key_map_);
        for (int i = 0; i < kNumberOfKeyCodes; ++i) {
            is_pressed_[i] = false;
            is_pressed_previously_[i] = false;
        }
    }
    ~KeyboardHandler() {}

    void HandleKeyDown(SDL_Keycode key);
    void HandleKeyUp(SDL_Keycode key);

    void Update();

    bool Presses(KeyCode key_code) const;
    bool Pressing(KeyCode key_code) const;
    bool Releases(KeyCode key_code) const;

private:
    std::unordered_map<SDL_KeyCode, int> key_map_;

    std::array<bool, kNumberOfKeyCodes> is_pressed_;
    std::array<bool, kNumberOfKeyCodes> is_pressed_previously_;
};

#endif  // RUMRAISIN_INTERFACES_KEYBOARD_H_
