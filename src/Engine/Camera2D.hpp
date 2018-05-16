//
// Created by Максим on 5/15/18.
//

#pragma once

#include "SDL.h"
#include "../Game/Game.hpp"

class Camera2D {
public:
    Camera2D(){}

    SDL_Rect* GetCameraRect()        { return &cameraRect; }
    void SetCameraX(float x)        { cameraRect.x = (int)x; }
private:
    SDL_Rect cameraRect = { 0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT };
};
