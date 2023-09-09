#include "SDL2/SDL.h"

#include "interfaces/general.h"

int main(int argc, char* argv[]) {
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
