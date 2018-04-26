//
//  Collisions.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Collisions_hpp
#define Collisions_hpp

#include <iostream>
#include <SDL2/SDL.h>

namespace Collisions
{
    bool Collides(const SDL_Rect &a, const SDL_Rect &b);
}

#endif /* Collisions_hpp */
