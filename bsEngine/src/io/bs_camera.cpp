//
// Created by bigsmarty on 11/13/21.
//

#include <main.h>
#include <base_engine/vk_engine.h>

using namespace std;

void bsEngine::camera()
{

    auto* keybState = SDL_GetKeyboardState(nullptr);
    if (keybState[SDL_SCANCODE_W])
    {
        camState.camMovement += camState.cameraFront * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_S])
    {
        camState.camMovement -= camState.cameraFront * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_A])
    {
        camState.camMovement += glm::cross(camState.cameraUp, camState.cameraFront) * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_D])
    {
        camState.camMovement -= glm::cross(camState.cameraUp, camState.cameraFront) * camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_LSHIFT])
    {
        camState.camMovement.y += camState.speed * _frametime;
    }
    if (keybState[SDL_SCANCODE_LCTRL])
    {
        camState.camMovement.y -= camState.speed * _frametime;
    }
    if(keybState[SDL_SCANCODE_ESCAPE])
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    camState.camMovement = glm::mix(glm::vec3(0.0f), camState.camMovement, 50.0f * _frametime);

    if (controllerHandling.numGamepads > 0)
    {
        float leftX = SDL_GameControllerGetAxis(controllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_LEFTX) / 32767;
        float leftY = SDL_GameControllerGetAxis(controllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_LEFTY) / 32767;
        float rightX = SDL_GameControllerGetAxis(controllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_RIGHTX) / 32767;
        float rightY = SDL_GameControllerGetAxis(controllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_RIGHTY) / 32767;

        camState.camMovement -= glm::cross(camState.cameraUp, camState.cameraFront) * camState.speed * _frametime * leftX;
        camState.camMovement -= camState.cameraFront * camState.speed * _frametime * leftY;
    }

}
