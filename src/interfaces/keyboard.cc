#include "interfaces/keyboard.h"

#include <unordered_map>

#include "SDL2/SDL.h"

namespace {

void DefaultKeyMap(std::unordered_map<SDL_KeyCode, int>& key_map) {
    key_map = {
        {SDLK_UP, static_cast<int>(KeyCode::kUp)},
        {SDLK_LEFT, static_cast<int>(KeyCode::kLeft)},
        {SDLK_RIGHT, static_cast<int>(KeyCode::kRight)},
        {SDLK_DOWN, static_cast<int>(KeyCode::kDown)},
    };
}

}  // namespace

void SetKeyMap(std::unordered_map<SDL_KeyCode, int>& key_map) {
    key_map.clear();
    // TODO: Load a key map file
    DefaultKeyMap(key_map);
}

void KeyboardHandler::HandleKeyDown(SDL_Keycode key) {
    SDL_KeyCode key_code = static_cast<SDL_KeyCode>(key);
    if (key_map_.find(key_code) != key_map_.end()) {
        int index = key_map_[key_code];
        is_pressed_[index] = true;
    }
}

void KeyboardHandler::HandleKeyUp(SDL_Keycode key) {
    SDL_KeyCode key_code = static_cast<SDL_KeyCode>(key);
    if (key_map_.find(key_code) != key_map_.end()) {
        int index = key_map_[key_code];
        is_pressed_[index] = false;
    }
}

void KeyboardHandler::Update() {
    for (int i = 0; i < kNumberOfKeyCodes; ++i) {
        is_pressed_previously_[i] = is_pressed_[i];
    }
}
