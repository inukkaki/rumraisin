#include "interfaces/general.h"

#include <iostream>
#include <string>

#include "SDL2/SDL.h"

#include "interfaces/config.h"

void ShowErrorMessage(const char* title, const char* message) {
    std::cerr << message << std::endl;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
}

void ShowErrorMessage(
        const char* title, const char* message, const char* quotation) {
    std::string error_msg = message;
    error_msg.append("\n> ");
    error_msg.append(quotation);
    std::cerr << error_msg << std::endl;
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, title, error_msg.c_str(), nullptr);
}

namespace {

bool InitSdl(Uint32 flags) {
    bool is_successful = true;
    if (SDL_Init(flags) < 0) {
        is_successful = false;
        ShowErrorMessage(
            "Initialization Error", "Could not initialize SDL:",
            SDL_GetError());
    }
    return is_successful;
}

bool CreateMainWindow(SDL_Window*& window) {
    bool is_successful = true;
    int window_width = WindowScale() * kWindowBaseWidth;
    int window_height = WindowScale() * kWindowBaseHeight;
    window = SDL_CreateWindow(
        kAppName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        window_width, window_height, SDL_WINDOW_SHOWN);
    if (!window) {
        is_successful = false;
        ShowErrorMessage(
            "Initialization Error", "Could not create a main window:",
            SDL_GetError());
    }
    return is_successful;
}

bool CreateRenderer(SDL_Window*& window, SDL_Renderer*& renderer) {
    bool is_successful = true;
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        is_successful = false;
        ShowErrorMessage(
            "Initialization Error", "Could not create a renderer:",
            SDL_GetError());
    }
    return is_successful;
}

}  // namespace

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    bool is_successful = false;
    if (InitSdl(SDL_INIT_VIDEO)) {
        if (CreateMainWindow(window)) {
            if (CreateRenderer(window, renderer)) {
                is_successful = true;
            }
        }
    }
    return is_successful;
}

void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    SDL_Quit();
}
