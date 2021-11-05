//
// Created by bigsmarty on 11/5/21.
//

#pragma once

#include <main.h>

class bsWindow
{
public:
    struct SDL_Window* _window{ nullptr };
    VkExtent2D _windowExtent{ 1700 , 900 };

    bsWindow();

};
