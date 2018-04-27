//
//  Actor.h
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include <SDL2/SDL.h>

class Actor
{
public:    
    virtual ~Actor() {}
    
    virtual void LoadContent() {}
    virtual void Update(SDL_Event* event) {}
    virtual void Render() {}
    virtual const SDL_Rect GetCollisionRect() = 0;
    virtual const SDL_Rect GetHitRect() = 0;
};

#endif /* Actor_h */
