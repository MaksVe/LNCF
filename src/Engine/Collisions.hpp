//
//  Collisions.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace Collisions
{
    bool Collides(const SDL_Rect &a, const SDL_Rect &b);
}
