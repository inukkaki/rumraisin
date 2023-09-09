#include "SDL2/SDL.h"

#include "interfaces/general.h"

int main(int argc, char* argv[]) {
    // just for debugging
    ShowErrorMessage("Test message", "This is a test!");
    ShowErrorMessage("Test message 2", "This is a test:", "quotation");
    return 0;
}
