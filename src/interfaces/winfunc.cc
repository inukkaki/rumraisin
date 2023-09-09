#include "interfaces/winfunc.h"

#include <iostream>

#if (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#endif

#include "SDL2/SDL.h"

namespace {

enum class ProcessDpiAwareness : unsigned char {
    kProcessDpiUnaware,
    kProcessSystemDpiAware,
    kProcessPerMonitorDpiAware
};

}  // namespace

// Reference:
// Eric Wasylishen's codes available at
// https://discourse.libsdl.org/t/sdl-getdesktopdisplaymode-resolution-
// reported-in-windows-10-when-using-app-scaling/22389/4
void ResolveBlurriness() {
    #if (defined(_WIN32) || defined(_WIN64))
    std::cout << "Executed on Microsoft Windows" << std::endl;
    std::cout << "Start to resolve the blurriness of the screen..."
              << std::endl;

    void* user_dll = nullptr;
    BOOL (WINAPI* SetProcessDPIAware)(void) = nullptr;
    void* shcore_dll = nullptr;
    HRESULT (WINAPI* SetProcessDpiAwareness)(int) = nullptr;

    // Access SetProcessDPIAware
    user_dll = SDL_LoadObject("USER32.DLL");
    if (user_dll) {
        std::cout << "Succeeded in accessing USER32.DLL" << std::endl;
        SetProcessDPIAware =
            (BOOL (WINAPI*)(void))
            SDL_LoadFunction(user_dll, "SetProcessDPIAware");
    }

    // Access SetProcessDpiAwareness
    shcore_dll = SDL_LoadObject("SHCORE.DLL");
    if (shcore_dll) {
        std::cout << "Succeeded in accessing SHCORE.DLL" << std::endl;
        SetProcessDpiAwareness =
            (HRESULT (WINAPI*)(int))
            SDL_LoadFunction(shcore_dll, "SetProcessDpiAwareness");
    } else {
        std::cout << "Failed in accessing SHCORE.DLL" << std::endl;
    }

    // Resolve the blurriness
    bool is_successful = true;
    if (SetProcessDpiAwareness) {
        std::cout << "Accessed SetProcessDpiAwareness()" << std::endl;
        HRESULT result = SetProcessDpiAwareness(
            static_cast<int>(ProcessDpiAwareness::kProcessPerMonitorDpiAware));
        if (result != S_OK) {
            is_successful = false;
        }
    } else if (SetProcessDPIAware) {
        std::cout << "Accessed SetProcessDPIAware()" << std::endl;
        BOOL result = SetProcessDPIAware();
        if (result == 0) {
            is_successful = false;
        }
    } else {
        is_successful = false;
    }

    // Report the result
    if (is_successful) {
        std::cout << "Succeeded in resolving the blurriness" << std::endl;
    } else {
        std::cout << "Failed in resolving the blurriness" << std::endl;
    }
    #endif
}
