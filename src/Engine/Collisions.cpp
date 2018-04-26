//
//  Collisions.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Collisions.hpp"

bool Collisions::Collides(const SDL_Rect &a, const SDL_Rect &b)
{
    if (a.x > (b.x + b.w)) return false;
    if ((a.x + a.w) < b.x) return false;
    if (a.y > (b.y + b.h)) return false;
    if ((a.y + a.h) < b.y) return false;
    
    return true;
}
