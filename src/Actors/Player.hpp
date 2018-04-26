//
//  Player.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>
#include "../Engine/Texture2D.hpp"
#include "../Engine/Timer.hpp"
#include "PlayerState.hpp"
#include "Actor.hpp"

/*Some parts of this class was originally from Lazy Foo' Productions
 (http://lazyfoo.net/)*/

class Player : public virtual Actor
{
public:
    Player(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Player();
    
    virtual void LoadContent();
    virtual void Update(SDL_Event* event);
    virtual void Render();
    
    virtual const SDL_Rect GetCollisionRect();
    
    void Move();
    void Animate(double delta, int maxFrames);
    
    enum State
    {
        IDLE,
        RUNNING,
        KICKING,
        PUNCHING,
        JUMPING,
        JUMPKICK
    };
    
    bool Animating(int maxFrames);
    
    State CurrentState = IDLE;
    
    static const int IDLE_FRAMES    = 4;
    static const int RUN_FRAMES     = 4;
    static const int KICK_FRAMES    = 4;
    static const int PUNCH_FRAMES   = 4;
    static const int JUMP_FRAMES    = 4;
    
    float velX = 0;
    float velY = 0;
    
    static constexpr float movementSpeed = 1.0f;
    
    enum class faceDirection
    {
        left,
        right,
    };
    
    faceDirection currentDirection = faceDirection::right;
    
    PlayerState* state;
    
    int frameToDraw = 0;
    int frameCount = 0;
    
    float posX = 100;
    float posY = 300;
    
    SDL_Rect collisionRect;
    SDL_Rect hitRect;
    
private:
    static const int VELOCITY = 1;
    
    const float animationSpeed = 7.0f;
    
    SDL_Renderer * renderer;
    SDL_Event* event;
    
    Texture2D* spriteSheet;
    
    SDL_Rect idleSpriteClips[IDLE_FRAMES];
    SDL_Rect runSpriteClips[RUN_FRAMES];
    SDL_Rect kickSpriteClips[KICK_FRAMES];
    SDL_Rect punchSpriteClips[PUNCH_FRAMES];
    SDL_Rect jumpSpriteClips[JUMP_FRAMES];
    SDL_Rect jumpKickClip;
    
    SDL_Rect* currentClip;
    
    int screenWidth;
    int screenHeight;

    float animUpdateTime = 1.0f / animationSpeed;
    float timeSinceLastFrame = 0.0f;
};

#endif /* Player_hpp */
