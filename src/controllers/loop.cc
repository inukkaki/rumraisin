#include "controllers/loop.h"

#include "SDL2/SDL.h"

#include "interfaces/config.h"
#include "interfaces/keyboard.h"
#include "interfaces/timer.h"

// just for debugging
#include <iostream>
#include "interfaces/graphics.h"
#include "models/entity.h"
#include "models/field.h"
#include "models/tile.h"

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
    EResource res;
    res.width = 14.0f;
    res.height = 20.0f;
    res.mass = 10.0f;
    res.air_drag_coefficient = 0.2f;
    Entity test_entity(
        res, kBControlPlayer, kBGetGravity, kBGetLinearAirDrag, kBUpdate);
    Vector2D test_g(0.0f, 0.1f);

    for (unsigned int tile_id = 0; tile_id < 4; ++tile_id) {
        std::cout << tile_id << ", " << GetTile(tile_id).debug_value
                  << std::endl;
    }
    Field test_field;
    test_field.Load();
    std::cout << test_field.GetCollision(0, 0).debug_value << std::endl;
    std::cout << test_field.GetCollision(
        kFieldMaxHeight - 1, kFieldMaxWidth - 1).debug_value << std::endl;
    std::cout << test_field.GetCollision(-1, 0).debug_value << std::endl;
    std::cout << test_field.GetCollision(0, -1).debug_value << std::endl;
    std::cout << test_field.GetCollision(
        kFieldMaxHeight, 0).debug_value << std::endl;
    std::cout << test_field.GetCollision(
        0, kFieldMaxWidth).debug_value << std::endl;

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
        test_entity.Control(kbd_handler);
        test_entity.GetGravity(test_g);
        test_entity.GetAirDrag();
        test_entity.Update();
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
