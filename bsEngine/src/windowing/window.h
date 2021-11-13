//
// Created by bigsmarty on 11/5/21.
//

#pragma once

#include "main.h"

class bsWindow
{
public:
    uint32_t windowWidth = 1700;
    uint32_t windowHeight = 900;

    struct SDL_Window* _window{ nullptr };
    VkExtent2D _windowExtent{ windowWidth , windowHeight };
    SDL_bool relativeMouseMode = SDL_TRUE;

    bsWindow();

};
