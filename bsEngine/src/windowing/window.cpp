//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include <windowing/window.h>

using namespace std;

bsWindow::bsWindow()
{

    // We initialize SDL and create a window with it.
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);

    _window = SDL_CreateWindow(
            "Vulkan Engine",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            _windowExtent.width,
            _windowExtent.height,
            window_flags
    );

    SDL_SetRelativeMouseMode(relativeMouseMode);

}
