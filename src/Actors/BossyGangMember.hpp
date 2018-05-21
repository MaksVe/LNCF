//
// Created by Максим on 5/21/18.
//

#pragma once

#include <iostream>
#include "SDL.h"
#include "../Engine/Texture2D.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/GameObject.hpp"
#include "Actor.hpp"

class Level_1;

class BossyGangMember : public virtual Actor
{
public:
    BossyGangMember(SDL_Renderer* renderer, Level_1* level1, int x, int y);
    ~BossyGangMember() override;

    void LoadContent() override;
    void HandleAction(double delta) override;
    void Update(SDL_Event* event, const Uint8* currentKeyStates) override;
    void Render(int camX) override;
    const SDL_Rect GetCollisionRect() override;
    const SDL_Rect GetHitRect() override;

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

    enum class FaceDirection
    {
        LEFT,
        RIGHT,
    };
    FaceDirection CurrentDirection = FaceDirection::LEFT;

    static constexpr float MovementSpeed = 0.9f;

    void FindNearestPlayer();
    void MoveToPlayer();
    void MoveAwayFromPlayer();
    void AttackPlayer();

    bool Attacking = false;
    bool PlayerAway = false;
    bool PlayerFarAway();

    int AttackCounter = 0;

    bool DoDamage() override;
    bool ReceiveDamage() override;

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

    static constexpr float VELOCITY = 0.9f;
    const float animationSpeed = 7.0f;
    float animUpdateTime = 1.0f / animationSpeed;
    float timeSinceLastFrame = 0.0f;

    Level_1* level1;
    Player* target;
};
