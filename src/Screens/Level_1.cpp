//
//  Level_1.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Level_1.hpp"

Level_1::Level_1(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer    = r;
    width       = screenWidth;
    height      = screenHeight;
    
    player              = new Player(renderer, width, height);
    pauseTextTexture    = new Texture2D(renderer);
    
    /* TODO: create a list of enemies,
     create methods to add and remove enemies,
     create a method to check player hit with enemy collisions,
     create a method to check player collision with enemy collisions...
     http://headerphile.blogspot.ru/2014/04/part-5-game-programming-in-sdl2.html
     */
    AddEnemy();
    
    LoadContent();
}


Level_1::~Level_1()
{
    delete player;
    delete pauseTextTexture;    
    for (auto &e: enemies)
    {
        delete e;
    }
}

void Level_1::LoadContent()
{
    player->LoadContent();
    
    pauseFont = TTF_OpenFont("Roboto-Black.ttf", 36);
    pauseTextTexture->LoadFromRenderedText("Paused", textColor, pauseFont);
}

void Level_1::Update(SDL_Event* e)
{
    event = e;
    
    if (!Paused)
    {
        player->Update(event);

        for (auto &e: enemies)
        {
            e->Update(event);
        }
        
        PlayerHitEnemyCollision();
    }
    
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.sym == SDLK_ESCAPE)
        {
            if (!Paused)
            {
                Paused = true;
            }
            else
            {
                Paused = false;
            }
            event->type = SDL_KEYUP;
            //ExitToMainMenu = true;
        }
    }
}

void Level_1::Render()
{
    player->Render();

    for (auto &e: enemies)
    {
        e->Render();
    }
    
    // --- pause text ---
    if (pauseFont != nullptr)
    {
        if (Paused)
        {
            pauseTextTexture->Render((width / 2) - (pauseTextTexture->GetWidth() / 2), (height / 2) - (pauseTextTexture->GetHeight() / 2));
        }
    }
}

void Level_1::AddEnemy()
{
    enemies.push_back(new FatGangMember(renderer, width, height));
}

bool Level_1::PlayerHitEnemyCollision()
{
    for (auto &e: enemies)
    {
        if (Collisions::Collides(player->hitRect, e->GetCollisionRect()))
        {
            std::cout << "collides" << std::endl;
            return true;
        }
    }
    
    return false;
}
