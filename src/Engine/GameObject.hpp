//
// Created by Максим on 5/10/18.
//

#pragma once

#include "SDL.h"

class GameObject
{
public:
    virtual ~GameObject()                   {}

    virtual void LoadContent()              {}
    virtual void Update(SDL_Event* event, const Uint8* currentKeyStates)   {}
    virtual void Render(int camX)                   {}

    virtual float GetPosY() { return PosY; }
    virtual float GetPosX() { return PosX; }

protected:
    float PosY{};
    float PosX{};
};
