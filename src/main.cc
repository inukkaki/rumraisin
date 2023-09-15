#include "SDL2/SDL.h"

#include "interfaces/general.h"
#include "interfaces/winfunc.h"

// just for debugging
#include <iostream>
#include "interfaces/config.h"
#include "interfaces/timer.h"

int main(int argc, char* argv[]) {
    // Resolve the blurriness of the screen (only for Microsoft Windows)
    ResolveBlurriness();

    // Initialization
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initialized_successfully = InitGui(window, renderer);

    // MAIN LOOP
    if (initialized_successfully) {
        // just for debugging
        SimpleTimer timer;

        const int& frame_rate = GetFrameRate();
        FrameRateBalancer fr_balancer(frame_rate);

        float measured_frame_rate = 0.0f;
        FrameRateMeasurer fr_measurer;

        timer.Set();
        fr_balancer.SetTimer();
        fr_measurer.SetTimer();
        while (timer.GetElapsedTime() < 5000) {
            if (fr_measurer.MeasureFrameRate(measured_frame_rate)) {
                std::cout << measured_frame_rate << " FPS" << std::endl;
            }
            fr_balancer.Delay();
            fr_balancer.SetTimer();
        }
    }

    // Deallocation
    CloseGui(window, renderer);

    return 0;
}
