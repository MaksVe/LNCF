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
    
    player              = new Player(renderer, this);
    pauseTextTexture    = new Texture2D(renderer);
    
    /* TODO: create a list of enemies,
     create methods to add and remove enemies,
     create a method to check player hit with enemy collisions,
     create a method to check player collision with enemy collisions...
     http://headerphile.blogspot.ru/2014/04/part-5-game-programming-in-sdl2.html
     */
    AddEnemy();
    CurrentEnemy = nullptr;

    LoadContent();
}


Level_1::~Level_1()
{
    delete player;
    delete pauseTextTexture;    
    for (auto &e : enemies)
    {
        delete e;
    }
}

void Level_1::LoadContent()
{
    player->LoadContent();
    
    pauseFont = TTF_OpenFont("PressStart2P.ttf", 16);
    pauseTextTexture->LoadFromRenderedText("Paused", textColor, pauseFont);

    levelTiledMap.LoadContent("level_01.tmx", renderer);
    upperCollider   = levelTiledMap.GetUpperEnd();
    rightCollider   = levelTiledMap.GetRightEnd();
    downerCollider  = levelTiledMap.GetDownerEnd();
    leftCollider    = levelTiledMap.GetLeftEnd();

    // store all our game objects in a vector
    gameObjects.push_back(player);
    for (auto& e : enemies)
    {
        gameObjects.push_back(e);
    }
}

void Level_1::Update(SDL_Event* e)
{
    event = e;
    
    if (!Paused)
    {
        player->Update(event);

        for (auto &e : enemies)
        {
            e->Update(event);
        }

        PlayerCollidesDown();
        PlayerCollidesEnemy();
        PlayerHitEnemyCollision();
        EnemyHitPlayerCollision();

        // sort all our game objects by their Y position
        std::sort(gameObjects.begin(), gameObjects.end(),
                  [](GameObject* a, GameObject* b) { return a->GetPosY() < b->GetPosY(); });
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
    levelTiledMap.Render(renderer);

    // draw all our game objects sorted by their Y position
    for (auto &o : gameObjects)
    {
        o->Render();
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
    enemies.push_back(new FatGangMember(renderer, this));
}



// --- Player Collisions --- //
bool Level_1::PlayerCollidesEnemy()
{
    for (auto &e : enemies)
    {
        if (Collisions::Collides(player->GetCollisionRect(), e->GetCollisionRect()))
        {
            //std::cout << "player collides enemy" << std::endl;
            // don't move any further
            return true;
        }
    }

    return false;
}

bool Level_1::PlayerHitEnemyCollision()
{
    for (auto &e : enemies)
    {
        if (Collisions::Collides(player->GetHitRect(), e->GetCollisionRect()))
        {
            //std::cout << "player hit rect collides enemy rect" << std::endl;
            CurrentEnemy = e;
            player->DoDamage();
            if (e->GetHP() <= 0)
            {
                std::cout << "enemy is dead" << std::endl;
                enemies.remove(e);
                delete e;
                CurrentEnemy = nullptr;
            }

            return true;
        }
    }
    
    return false;
}

bool Level_1::PlayerCollidesUp()
{
    return Collisions::Collides(player->GetCollisionRect(), upperCollider);
}

bool Level_1::PlayerCollidesLeft()
{
    return Collisions::Collides(player->GetCollisionRect(), leftCollider);
}

bool Level_1::PlayerCollidesRight()
{
    return Collisions::Collides(player->GetCollisionRect(), rightCollider);
}

bool Level_1::PlayerCollidesDown()
{
    return Collisions::Collides(player->GetCollisionRect(), downerCollider);
}
// --- Player Collisions --- //



// --- Enemy Collisions --- //
bool Level_1::EnemyHitPlayerCollision()
{
    for (auto &e: enemies)
    {
        if (Collisions::Collides(e->GetHitRect(), player->GetCollisionRect()))
        {
            //std::cout << "enemy hit rect collides player rect" << std::endl;
            CurrentEnemy = e;
            player->ReceiveDamage();
            if (player->GetHP() <= 0)
            {
                std::cout << "player is dead" << std::endl;
            }

            return true;
        }
    }

    return false;
}

SDL_Rect Level_1::GetLevelUpperCollider()
{
    return upperCollider;
}

SDL_Rect Level_1::GelLevelDownerCollider()
{
    return downerCollider;
}
// --- Enemy Collisions --- //

Player* Level_1::FindPlayer()
{
    return player;
}

int Level_1::GetScreenWidth()
{
    return width;
}

int Level_1::GetScreenHeight()
{
    return height;
}
