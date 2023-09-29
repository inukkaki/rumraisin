#include "controllers/loop.h"

#include "SDL2/SDL.h"

#include "interfaces/config.h"
#include "interfaces/keyboard.h"
#include "interfaces/timer.h"

// just for debugging
#include <iostream>
#include "interfaces/graphics.h"
#include "models/entity.h"

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
    Entity test_entity;
    EResource& res = test_entity.res();
    res.width = 14.0f;
    res.height = 20.0f;
    res.r.Set(10.0f, 5.0f);
    res.v.Set(1.0f, -0.5f);
    res.a.Set(-0.1f, 0.2f);

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
        RenderEntityDebugInfo(renderer, test_entity.res());

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
