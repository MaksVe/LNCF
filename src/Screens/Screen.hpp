//
//  Screen.h
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>

class Screen
{
public:
    virtual ~Screen() {}

    virtual void LoadContent() {}
    virtual void Update(SDL_Event* event) {}
    virtual void Render() {}
};
