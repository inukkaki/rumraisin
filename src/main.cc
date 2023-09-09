#include "SDL2/SDL.h"

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
        // just for debugging
        ShowErrorMessage("Test message", "This is a test!");
        ShowErrorMessage("Test message 2", "This is a test:", "quotation");
    }

    // Deallocation
    CloseGui(window, renderer);

    return 0;
}
