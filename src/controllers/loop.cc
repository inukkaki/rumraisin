#include "controllers/loop.h"

#include "SDL2/SDL.h"

#include "interfaces/config.h"
#include "interfaces/timer.h"

// just for debugging
#include <iostream>

namespace {

bool HandleEvents() {
    bool app_is_running = true;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            app_is_running = false;
            break;
        default:
            break;
        }
    }
    return app_is_running;
}

}  // namespace

void MainLoop(bool& app_is_running) {
    // Handle the frame rate on this loop
    FrameRateBalancer fr_balancer(GetFrameRate());
    FrameRateMeasurer fr_measurer;
    float measured_frame_rate = 0.0f;

    // LOOP
    fr_balancer.SetTimer();
    fr_measurer.SetTimer();
    while (app_is_running) {
        // Handle events
        app_is_running = HandleEvents();

        // Measure the frame rate
        if (fr_measurer.MeasureFrameRate(measured_frame_rate)) {
            // just for debugging
            std::cout << measured_frame_rate << " FPS" << std::endl;
        }

        // Balance the frame rate
        fr_balancer.Delay();
        fr_balancer.SetTimer();
    }
}
