#ifndef RUMRAISIN_INTERFACES_GENERAL_H_
#define RUMRAISIN_INTERFACES_GENERAL_H_

#include "SDL2/SDL.h"

void ShowErrorMessage(const char* title, const char* message);
void ShowErrorMessage(
        const char* title, const char* message, const char* quotation);

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer);
void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer);

#endif  // RUMRAISIN_INTERFACES_GENERAL_H_
