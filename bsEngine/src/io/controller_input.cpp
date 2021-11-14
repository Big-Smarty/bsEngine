//
// Created by bigsmarty on 11/14/21.
//

#include "controller_input.h"
using namespace std;

GamePadHandling::GamePadHandling()
{
    //InitializeControllers();
}

void GamePadHandling::InitializeControllers()
{
    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) != 1)
    {
        SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
        cout << "Successfully initialised the GameController subsystem!\n";
    }

    int nJoysticks = SDL_NumJoysticks();
    numGamepads = 0;

    //count the amount of controllers available
    for (int i = 0; i < nJoysticks; i++)
    {
        if (SDL_IsGameController(i))
            numGamepads++;
    }

    cout << "Number of gamepads available: " << numGamepads << endl;

    //add controllers to array if any are connected
    if (numGamepads > 0)
    {
        for (int i = 0; i < numGamepads; i++)
        {
            SDL_GameController* pad = SDL_GameControllerOpen(i);
            if (SDL_GameControllerGetAttached(pad) == 1)
            {
                connectedControllers.push_back(pad);
            }
            else
            {
                cerr << "SDL_GetError(): " << SDL_GetError() << endl;
            }
        }
        SDL_GameControllerEventState(SDL_ENABLE);
    }

    //initialize input arrays with the size of the amount of gamepads
    controllerInputs.resize(numGamepads);
    lastControllerInputs.resize(numGamepads);

    //initialize all axis and buttons to 0/false to prevent undefined behaviour
    for (int i = 0; i < numGamepads; i++)
    {
        for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
        {
            controllerInputs[i].axis[a] = 0;
            lastControllerInputs[i].axis[a] = 0;
        }
        for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
        {
            controllerInputs[i].buttons[b] = false;
            lastControllerInputs[i].buttons[b] = false;
        }
    }
}


void GamePadHandling::Update()
{
    SDL_Event conEvent;
    if (SDL_PollEvent(&conEvent))
    {
        /*switch(conEvent.type)
        {
            //if new controller is added
            case SDL_CONTROLLERDEVICEADDED:
                cout << "New controller device was added: " << conEvent.cdevice.which << endl;
                break;

            //if button is pressed
            case SDL_CONTROLLERBUTTONDOWN:
                for (int i = 0; i < numGamepads; i++)
                {
                    if (conEvent.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i])))
                    {
                        controllerInputs[i].buttons[conEvent.cbutton.button] = true;
                    }
                }
                break;

                //if button is pressed
            case SDL_CONTROLLERBUTTONUP:
                for (int i = 0; i < numGamepads; i++)
                {
                    if (conEvent.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i])))
                    {
                        controllerInputs[i].buttons[conEvent.cbutton.button] = false;
                    }
                }
                break;

            //if theres axis motion
            case SDL_CONTROLLERAXISMOTION:
                for (int i = 0; i < numGamepads; i++)
                {
                    if (conEvent.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i])))
                    {
                        controllerInputs[i].axis[conEvent.caxis.axis] = conEvent.caxis.value;
                    }
                }
                break;
        }*/
    }

    //set axis and buttons of lastControllerInputs to the ones of controllerInputs
    for (int i = 0; i < numGamepads; i++)
    {
        for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
        {
            lastControllerInputs[i].axis[a] = controllerInputs[i].axis[a];
        }
        for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
        {
            lastControllerInputs[i].buttons[b] = controllerInputs[i].buttons[b];
        }
    }
}

float GamePadHandling::isControllerButtonPressed(GamePadHandling::Controllers controllerID, SDL_GameControllerButton button)
{
    //if the controllerID is invalid, return false
    if (controllerID < 0 || controllerID > numGamepads)
    {
        return 0.0f;
    }

    return controllerInputs[controllerID].buttons[button] && !lastControllerInputs[controllerID].buttons[button];
}

float GamePadHandling::isControllerButtonHeld(Controllers controllerID, SDL_GameControllerButton button)
{
    //if the controllerID is invalid, return false
    if (controllerID < 0 || controllerID > numGamepads)
    {
        return 0.0f;
    }

    return controllerInputs[controllerID].buttons[button] && lastControllerInputs[controllerID].buttons[button];
}

float GamePadHandling::getControllerAxis(Controllers controllerID, SDL_GameControllerAxis axis)
{
    //if the controllerID is invalid, return false
    if (controllerID < 0 || controllerID > numGamepads)
    {
        return 0.0f;
    }

    return controllerInputs[controllerID].axis[axis] / 32768.0f;
}