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
        camState.camMovement += camState.cameraFront * camState.speed * frametime;
    }
    if (keybState[SDL_SCANCODE_S])
    {
        camState.camMovement -= camState.cameraFront * camState.speed * frametime;
    }
    if (keybState[SDL_SCANCODE_A])
    {
        camState.camMovement += glm::cross(camState.cameraUp, camState.cameraFront) * camState.speed * frametime;
    }
    if (keybState[SDL_SCANCODE_D])
    {
        camState.camMovement -= glm::cross(camState.cameraUp, camState.cameraFront) * camState.speed * frametime;
    }
    if (keybState[SDL_SCANCODE_LSHIFT])
    {
        camState.camMovement.y += camState.speed * frametime;
    }
    if (keybState[SDL_SCANCODE_LCTRL])
    {
        camState.camMovement.y -= camState.speed * frametime;
    }
    if(keybState[SDL_SCANCODE_ESCAPE])
    {
        bQuit = true;
    }

    camState.camMovement = glm::mix(glm::vec3(0.0f), camState.camMovement, 50.0f * frametime);

    if (oControllerHandling.numGamepads > 0)
    {
        oInput.conRightX = SDL_GameControllerGetAxis(oControllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_RIGHTX);
        //cout << "conRightX: " << oInput.conRightX << endl;
        oInput.conRightY = SDL_GameControllerGetAxis(oControllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_RIGHTY);
        //cout << "conRightY: " << oInput.conRightY << endl;

        mouseInput.GetMouseDiff(oInput.xOffset, oInput.yOffset);

        if (oInput.conRightX >= 2000.0f | oInput.conRightX <= -2000.0f )
        {
            camState.yaw += oInput.conRightX / 32767.0f;
        }

        if (oInput.conRightY >= 2000.0f | oInput.conRightY <= -2000.0f )
        {
            camState.pitch -= oInput.conRightY / 32767.0f;
        }

        SDL_GameControllerUpdate();
        float leftX = SDL_GameControllerGetAxis(oControllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
        //cout << "Controller left x state: " << SDL_GameControllerGetAxis(oControllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_LEFTX) << endl;
        SDL_GameControllerUpdate();
        float leftY = SDL_GameControllerGetAxis(oControllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;
        //cout << "Controller left y state: " << SDL_GameControllerGetAxis(oControllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_LEFTY) << endl;

        if (leftX >= 2000.0f / 32767.0f | leftX <= -2000.0f / 32767.0f)
        {
            camState.camMovement -= glm::cross(camState.cameraUp, camState.cameraFront) * camState.speed * frametime * leftX;
        }
        if (leftY >= 2000.0f / 32767.0f | leftY <= -2000.0f / 32767.0f)
        {
            camState.camMovement -= camState.cameraFront * camState.speed * frametime * leftY;
        }
    }

    camState.yaw += oInput.xOffset;
    camState.pitch -= oInput.yOffset;

    if(camState.pitch > 85.0f)
        camState.pitch = 85.0f;
    if(camState.pitch < -85.0f)
        camState.pitch = -85.0f;

    camState.direction.x = cos(glm::radians(camState.yaw)) * cos(glm::radians(camState.pitch));
    camState.direction.y = sin(glm::radians(camState.pitch));
    camState.direction.z = sin(glm::radians(camState.yaw)) * cos(glm::radians(camState.pitch));
    camState.cameraFront = glm::normalize(camState.direction);

    camState.camPos += camState.camMovement;

    camState.view = glm::lookAt(camState.camPos, camState.camPos + camState.cameraFront, camState.cameraUp);

    camState.projection = glm::perspective(glm::radians(70.0f), 1700.0f / 900.0f, 0.1f, 200.0f);
    camState.projection[1][1] *= -1;

}
