//
// Created by bigsmarty on 11/13/21.
//

#pragma once

#include <main.h>

/**
 *  Used as a mask when testing buttons in buttonstate.
 *   - Button 1:  Left mouse button
 *   - Button 2:  Middle mouse button
 *   - Button 3:  Right mouse button
 */
#define SDL_BUTTON(X)       (1 << ((X)-1))
#define SDL_BUTTON_LEFT     1
#define SDL_BUTTON_MIDDLE   2
#define SDL_BUTTON_RIGHT    3
#define SDL_BUTTON_X1       4
#define SDL_BUTTON_X2       5
#define SDL_BUTTON_LMASK    SDL_BUTTON(SDL_BUTTON_LEFT)
#define SDL_BUTTON_MMASK    SDL_BUTTON(SDL_BUTTON_MIDDLE)
#define SDL_BUTTON_RMASK    SDL_BUTTON(SDL_BUTTON_RIGHT)
#define SDL_BUTTON_X1MASK   SDL_BUTTON(SDL_BUTTON_X1)
#define SDL_BUTTON_X2MASK   SDL_BUTTON(SDL_BUTTON_X2)

class InputMouse
{
public:
    ///--- Constructor/Destructor
    //InputMouse();
    //~InputMouse();

    ///--- Object control
    bool Initialize();
    void Update();
    //void Release();

    ///--- To receive SDL_MouseWheelEvent
    void ReceiveEvent(const SDL_Event& oEvent);

    ///--- Mouse position fucntions
    void GetMousePosition(int& iCoordX, int& iCoordY) const;
    void GetMouseDiff(float& iDiffX, float& iDiffY) const;

    ///--- Mouse button states
    bool IsButtonTriggered(const Uint32 uButton) const;
    bool IsButtonPressed(const Uint32 uButton) const;
    bool IsButtonReleased(const Uint32 uButton) const;

    ///--- Wheel state
    int GetWheelX() const;
    int GetWheelY() const;
private:
    /// Information about the state of the mouse
    int m_iCurrentCoordX;
    int m_iCurrentCoordY;
    Uint32 m_uCurrentMouseState;

    int m_iPreviousCoordX;
    int m_iPreviousCoordY;
    Uint32 m_uPreviousMouseState;

    ///information about the state of thw wheel
    Sint32 m_iWheelX;
    Sint32 m_iWheelY;
};

