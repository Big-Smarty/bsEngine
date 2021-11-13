//
// Created by bigsmarty on 11/13/21.
//

#include <main.h>
#include <vk_engine.h>
#include <glm/gtx/transform.hpp>

using namespace std;

void bsEngine::camera()
{

    auto* keybState = SDL_GetKeyboardState(nullptr);
    if (keybState[SDL_SCANCODE_W])
    {
        camMovement += cameraFront * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_S])
    {
        camMovement -= cameraFront * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_A])
    {
        camMovement += glm::cross(cameraUp, cameraFront) * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_D])
    {
        camMovement -= glm::cross(cameraUp, cameraFront) * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_LSHIFT])
    {
        camMovement.y += camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_LCTRL])
    {
        camMovement.y -= camState.speed * _frametime;
    }
    if(keybState[SDL_SCANCODE_ESCAPE])
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }

}
