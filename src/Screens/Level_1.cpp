//
//  Level_1.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Level_1.hpp"

#include "../Engine/Camera2D.hpp"


Level_1::Level_1(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer    = r;
    width       = screenWidth;
    height      = screenHeight;
    
    player              = new Player(renderer, this);
    pauseTextTexture    = new Texture2D(renderer);
    camera              = new Camera2D();

    // http://headerphile.blogspot.ru/2014/04/part-5-game-programming-in-sdl2.html
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
    levelTiledMap.LoadForeground("level_01.tmx", renderer);

    upperCollider   = levelTiledMap.GetUpperEnd();
    rightCollider   = levelTiledMap.GetRightEnd();
    downerCollider  = levelTiledMap.GetDownerEnd();
    leftCollider    = levelTiledMap.GetLeftEnd();

    levelWidth = levelTiledMap.MapWidth;

    // store all our game objects in a vector
    gameObjects.push_back(player);
    for (auto& e : enemies)
    {
        gameObjects.push_back(e);
    }
}

void Level_1::Update(SDL_Event* e, const Uint8* currentKeyStates)
{
    event = e;
    
    if (!Paused)
    {
        for (auto& o : gameObjects)
        {
            o->Update(e, currentKeyStates);
        }

        if (enemies.empty())
        {
            AddEnemy();
        }

        if (player->GetPosX() > levelTiledMap.GetEndPoint().x)
        {
            PlayerWon = true;
        }

        PlayerCollidesDown();
        PlayerCollidesEnemy();
        EnemyCollidesEnemy();
        PlayerHitEnemyCollision();
        EnemyHitPlayerCollision();
        EnemyWaitsEnemy();

        // sort all our game objects by their Y position
        std::sort(gameObjects.begin(), gameObjects.end(),
                  [](GameObject* a, GameObject* b) { return a->GetPosY() < b->GetPosY(); });

        camera->SetCameraX(player->GetPosX());
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
    levelTiledMap.Render(renderer, camera->GetCameraRect());

    // draw all our game objects sorted by their Y position
    for (auto &o : gameObjects)
    {
        o->Render(camera->GetCameraRect()->x);
    }

    levelTiledMap.RenderForeground(renderer, camera->GetCameraRect());

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
    enemies.push_back(new FatGangMember(renderer, this, 400, 155));
//    enemies.push_back(new FatGangMember(renderer, this, 385, 142));
    enemies.push_back(new FastGangMember(renderer, this, 415, 149));
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
            if (player->GetPosY() == e->GetPosY())
            {
                player->SetState(new IdleState());
            }

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

            if (player->DoDamage())
            {
                CurrentEnemy->CurrentState = CurrentEnemy->STAGGERED;
            }


            // DELETE THE SHIT OUT OF IT
            if (e->GetHP() <= 0)
            {
                std::cout << "enemy is dead" << std::endl;

                enemies.remove(e);

                auto it = std::find(gameObjects.begin(), gameObjects.end(), e);
                if (it == gameObjects.end())
                {
                    // oops
                }
                else
                {
                    auto index = std::distance(gameObjects.begin(), it);
                    gameObjects.erase(gameObjects.begin() + index);
                }

                // IT DOESN'T WORK? I STILL GOT ENEMIES IN MY VECTOR BRAHW
                delete e;
                e = nullptr;
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

            if (CurrentEnemy->DoDamage())
            {
                player->SetState(new StaggeredState);
            }


            if (player->GetHP() <= 0)
            {
                std::cout << "player is dead" << std::endl;
                PlayerLost = true;
            }

            return true;
        }
    }

    return false;
}

bool Level_1::EnemyCollidesEnemy()
{
    // probably can be void
    // bs anyway
    for (auto &e : enemies)
    {
        for (auto &ne : enemies)
        {
            if (e == ne)
            {
                continue;
            }

            if (Collisions::Collides(e->GetCollisionRect(), ne->GetCollisionRect()))
            {
                if (isInBound(e->GetPosY(), ne->GetPosY() - 0.3f, ne->GetPosY() + 0.3f))
                {
                    if (e->GetCollisionRect().x + e->GetCollisionRect().w >= ne->GetCollisionRect().x)
                    {
                        e->CurrentState = e->IDLE;

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Level_1::EnemyWaitsEnemy()
{
    // probably can be void
    // bullshit as always, since they can both get in attacking state and freeze forever
    for (auto &e : enemies)
    {
        for (auto &ne : enemies)
        {
            if (e == ne)
            {
                continue;
            }

            if (ne->CurrentState == ne->ATTACKING)
            {
                e->CurrentState = e->IDLE;

                return true;
            }
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
    if (player == nullptr)
    {
        std::cout << "player is null" << std::endl;

        return nullptr;
    }
    else
    {
        return player;
    }
}

int Level_1::GetScreenWidth()
{
    return width;
}

int Level_1::GetScreenHeight()
{
    return height;
}
