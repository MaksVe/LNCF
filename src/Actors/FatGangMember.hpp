//
//  Enemy_1.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef FatGangMember_hpp
#define FatGangMember_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include "../Engine/Texture2D.hpp"
#include "../Engine/Timer.hpp"
#include "Actor.hpp"

class FatGangMember : public virtual Actor
{
public:
    FatGangMember(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~FatGangMember();
    
    virtual void LoadContent();
    virtual void Update(SDL_Event* event);
    virtual void Render();
    
    virtual const SDL_Rect GetCollisionRect();
    
    float posX = 400;
    float posY = 300;
    
private:
    SDL_Renderer* renderer;
    SDL_Event* event;
    
    SDL_Rect collisionRect;
    
    int screenWidth;
    int screenHeight;
};

#endif /* FatGangMember_hpp */
