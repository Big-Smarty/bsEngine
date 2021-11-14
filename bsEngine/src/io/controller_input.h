//
// Created by bigsmarty on 11/14/21.
//

#pragma once

#include <main.h>

struct GamePad
{
    bool buttons[SDL_CONTROLLER_BUTTON_MAX];
    int axis[SDL_CONTROLLER_AXIS_MAX];
};

class GamePadHandling
{
public:
    GamePadHandling();
    void InitializeControllers();
    void Update();

    enum Controllers {PLAYER1, PLAYER2, PLAYER3, PLAYER4};

    std::vector<SDL_GameController*> connectedControllers;
    std::vector<GamePad> controllerInputs;
    std::vector<GamePad> lastControllerInputs;
    int numGamepads{};

    float isControllerButtonPressed(Controllers controllerID, SDL_GameControllerButton button);
    float isControllerButtonHeld(Controllers controllerID, SDL_GameControllerButton button);

    float getControllerAxis(Controllers controllerID, SDL_GameControllerAxis axis);

};