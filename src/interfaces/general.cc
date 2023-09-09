#include "interfaces/general.h"

#include <iostream>
#include <string>

#include "SDL2/SDL.h"

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
