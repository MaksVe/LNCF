//
//  Level_1.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include "Screen.hpp"
#include "../Actors/Actor.hpp"
#include "../Actors/Player.hpp"
#include "../Actors/FatGangMember.hpp"
#include "../Actors/FastGangMember.hpp"
#include "../Actors/BossyGangMember.hpp"
#include "../Engine/Collisions.hpp"
#include "../Engine/GameObject.hpp"
#include "../Engine/TiledMap.hpp"

class Camera2D;

class Level_1 : public virtual Screen
{
public:
    Level_1(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Level_1() override;

    void LoadContent() override;
    void Update(SDL_Event* event, const Uint8* currentKeyStates) override;
    void Render() override;

    void AddEnemy();

    // Wave spawn instead of adding enemies
    void SpawnWave1();
    void SpawnWave2();
    void SpawnWave3();
    void SpawnWave4();

    // Player Collisions
    bool PlayerCollidesEnemy();
    bool PlayerHitEnemyCollision();
    bool PlayerCollidesUp();
    bool PlayerCollidesRight();
    bool PlayerCollidesDown();
    bool PlayerCollidesLeft();

    // Enemy Collisions
    bool EnemyHitPlayerCollision();
    bool EnemyCollidesEnemy();
    SDL_Rect GetLevelUpperCollider();
    SDL_Rect GelLevelDownerCollider();

    int GetScreenWidth();
    int GetScreenHeight();

    Player* FindPlayer();
    bool EnemyWaitsEnemy();
    bool PlayerIsBusy();

    Actor* CurrentEnemy;

    bool Paused = false;
    bool PlayerWon = false;
    bool PlayerLost = false;
    bool ExitToMainMenu = false;

private:
    SDL_Renderer * renderer;
    SDL_Event* event;
    SDL_Color textColor = { 255, 255, 255  };

    int width;
    int height;

    TTF_Font* pauseFont;
    Texture2D* pauseTextTexture;
    Texture2D* endTexture;
    Texture2D* hpTexture;

    // Actors
    Player* player;
    std::list<Actor*> enemies;

    TiledMap levelTiledMap = TiledMap("Level 01");
    float levelWidth;

    // Vector of all our level objects including player and enemies
    std::vector<GameObject*> gameObjects;

    // map colliders
    SDL_Rect upperCollider;
    SDL_Rect rightCollider;
    SDL_Rect downerCollider;
    SDL_Rect leftCollider;

    SDL_Rect healthBar;

    Camera2D* camera;
    tile* t;

    template <typename T>
    bool isInBound(const T& value, const T& low, const T& high)
    {
        return !(value < low) && (high < value);
    }

    int waveCounter;
};
