//
//  Enemy_1.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <iostream>
#include "SDL.h"
#include "../Engine/Texture2D.hpp"
#include "../Engine/Timer.hpp"
#include "Actor.hpp"
#include "ActorState.hpp"

class Level_1;

class FatGangMember : public virtual Actor
{
public:
    FatGangMember(SDL_Renderer* renderer, Level_1* level1);
    ~FatGangMember() override;

    void LoadContent() override;
    void Update(SDL_Event* event) override;
    void Render() override;
    const SDL_Rect GetCollisionRect() override;
    const SDL_Rect GetHitRect() override;

    float posX = 400;
    float posY = 300;
    float VelX = 0;
    float VelY = 0;
    void Move();

    void Animate(double delta, int maxFrames);
    bool Animating(int maxFrames);

    static const int IDLE_FRAMES    = 4;
    static const int RUN_FRAMES     = 4;
    static const int ATTACK_FRAMES  = 3;
    int FrameToDraw = 0;
    int FrameCount = 0;
    enum class State
    {
        IDLE,
        RUNNING,
        ATTACKING
    };
    State CurrentState = State::IDLE;
    ActorState* state;

    enum class FaceDirection
    {
        LEFT,
        RIGHT,
    };
    FaceDirection CurrentDirection = FaceDirection::LEFT;

    static constexpr float MovementSpeed = 1.0f;

    void FindNearestPlayer();
    void MoveToPlayer();
    void MoveAwayFromPlayer();
    void AttackPlayer();

    bool Attacking = false;
    bool PlayerAway = false;
    bool PlayerFarAway();

    int AttackCounter = 0;

    void DoDamage() override;
    void ReceiveDamage() override;
    int GetHP() override;

    bool ReceivingDamage = false;

private:
    SDL_Renderer* renderer;
    SDL_Event* event;
    SDL_Rect collisionRect;
    SDL_Rect hitRect;
    Texture2D* spriteSheet;
    Timer* timer;

    SDL_Rect idleSpriteClips[IDLE_FRAMES];
    SDL_Rect runSpriteClips[RUN_FRAMES];
    SDL_Rect attackSpriteClips[ATTACK_FRAMES];
    SDL_Rect* currentClip;

    int screenWidth;
    int screenHeight;

    static const int VELOCITY = 1;
    const float animationSpeed = 7.0f;
    float animUpdateTime = 1.0f / animationSpeed;
    float timeSinceLastFrame = 0.0f;

    Level_1* level1;
    Player* target;

    int HP;
};
