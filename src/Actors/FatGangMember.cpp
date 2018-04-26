//
//  Enemy_1.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "FatGangMember.hpp"

FatGangMember::FatGangMember(SDL_Renderer* r, int gameScreenWidth, int gameScreenHeight)
{
    renderer = r;
    screenWidth = gameScreenWidth;
    screenHeight = gameScreenHeight;
    
    collisionRect.x = posX;
    collisionRect.y = posY;
    collisionRect.w = 14;
    collisionRect.h = 28;
    
    LoadContent();
}

FatGangMember::~FatGangMember()
{
    
}

void FatGangMember::LoadContent()
{
    
}

void FatGangMember::Update(SDL_Event *e)
{
    event = e;
    
    collisionRect.x = posX + 17;    // we don't need the whole frame (48x48), because
    collisionRect.y = posY + 20;    // it's too big for our collision rect (hitbox)
}

void FatGangMember::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
    SDL_RenderDrawRect(renderer, &collisionRect);
}

const SDL_Rect FatGangMember::GetCollisionRect()
{
    return collisionRect;
}
