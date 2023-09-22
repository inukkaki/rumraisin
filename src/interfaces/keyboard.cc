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
