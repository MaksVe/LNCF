//
//  Level_1.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Level_1_hpp
#define Level_1_hpp

#include <list>
#include "Screen.hpp"
#include "../Actors/Actor.hpp"
#include "../Actors/Player.hpp"
#include "../Actors/FatGangMember.hpp"
#include "../Engine/Collisions.hpp"

class Level_1 : public virtual Screen
{
public:
    Level_1(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Level_1() override;
    
    void LoadContent() override;
    void Update(SDL_Event* event) override;
    void Render() override;
    
    void AddEnemy();

    bool PlayerCollidesEnemy();
    bool PlayerHitEnemyCollision();
    bool EnemyHitPlayerCollision();

    int GetScreenWidth();
    int GetScreenHeight();
    Player* FindPlayer();
    Actor* CurrentEnemy;
    
    bool Paused = false;
    bool ExitToMainMenu = false;
    
private:
    SDL_Renderer * renderer;
    SDL_Event* event;
    SDL_Color textColor = { 0, 0, 0 };
    
    int width;
    int height;
    
    TTF_Font* pauseFont;
    Texture2D* pauseTextTexture;
    
    // Actors
    Player* player;
    std::list<Actor*> enemies;
    std::list<Actor*>::iterator enemyIt;
};

#endif /* Level_1_hpp */
