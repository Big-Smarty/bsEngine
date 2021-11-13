//
// Created by bigsmarty on 11/6/21.
//

#include "main.h"
#include "vk_engine.h"

float bsEngine::frametimeCounter()
{

    const auto current_time = std::chrono::high_resolution_clock::now();
    auto frametime = std::chrono::duration<float, std::chrono::seconds::period>(current_time - last_time).count();

    //std::cout << "Frametime: " << frametime << "ms" << std::endl;

    last_time = current_time;

    return frametime;
}