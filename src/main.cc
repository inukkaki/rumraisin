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
        const int& frame_rate = GetFrameRate();
        std::cout << frame_rate << std::endl;
        int count = 0;
        SimpleTimer timer;
        timer.Set();
        while (count < 5) {
            if (timer.GetElapsedTime() > 1000) {
                ++count;
                timer.Set();
                std::cout << "1 sec elapsed" << std::endl;
            }
        }
    }

    // Deallocation
    CloseGui(window, renderer);

    return 0;
}
