#include "SDL2/SDL.h"

#include "controllers/loop.h"
#include "interfaces/general.h"
#include "interfaces/winfunc.h"

int main(int argc, char* argv[]) {
    // Resolve the blurriness of the screen (only for Microsoft Windows)
    ResolveBlurriness();

    // Initialization
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initialized_successfully = InitGui(window, renderer);

    // MAIN LOOP
    if (initialized_successfully) {
        bool app_is_running = true;
        MainLoop(app_is_running, renderer);
    }

    // Deallocation
    CloseGui(window, renderer);

    return 0;
}
