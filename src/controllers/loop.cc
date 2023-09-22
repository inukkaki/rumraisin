#include "controllers/loop.h"

#include "SDL2/SDL.h"

#include "interfaces/config.h"
#include "interfaces/keyboard.h"
#include "interfaces/timer.h"

// just for debugging
#include <iostream>

namespace {

bool HandleEvents(KeyboardHandler& kbd_handler) {
    bool app_is_running = true;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            app_is_running = false;
            break;
        case SDL_KEYDOWN:
            kbd_handler.HandleKeyDown(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            kbd_handler.HandleKeyUp(event.key.keysym.sym);
            break;
        default:
            break;
        }
    }
    return app_is_running;
}

}  // namespace

void MainLoop(bool& app_is_running, SDL_Renderer* const renderer) {
    // Handle the keyboard
    KeyboardHandler kbd_handler;

    // Handle the frame rate on this loop
    FrameRateBalancer fr_balancer(GetFrameRate());
    FrameRateMeasurer fr_measurer;
    float measured_frame_rate = 0.0f;

    // just for debugging
    KeyCode key_code;
    SDL_Rect rect;

    // LOOP
    fr_balancer.SetTimer();
    fr_measurer.SetTimer();
    while (app_is_running) {
        // Handle events
        app_is_running = HandleEvents(kbd_handler);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // just for debugging
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (int i = 0; i < kNumberOfKeyCodes; ++i) {
            key_code = static_cast<KeyCode>(i);
            if (kbd_handler.Presses(key_code)) {
                rect = {16 * i, 0, 16, 16};
                SDL_RenderFillRect(renderer, &rect);
            }
            if (kbd_handler.Pressing(key_code)) {
                rect = {16 * i, 16, 16, 16};
                SDL_RenderFillRect(renderer, &rect);
            }
            if (kbd_handler.Releases(key_code)) {
                rect = {16 * i, 32, 16, 16};
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        // Measure the frame rate
        if (fr_measurer.MeasureFrameRate(measured_frame_rate)) {
            // just for debugging
            std::cout << measured_frame_rate << " FPS" << std::endl;
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Update the keyboard handler
        kbd_handler.Update();

        // Balance the frame rate
        fr_balancer.Delay();
        fr_balancer.SetTimer();
    }
}
