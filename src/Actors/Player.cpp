//
//  Player.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Player.hpp"
#include "../Screens/Level_1.hpp"
#include <type_traits>
#include <typeinfo>

Player::Player(SDL_Renderer* r, Level_1* l1)
{
    renderer = r;
    level1 = l1;
    screenWidth = l1->GetScreenWidth();
    screenHeight = l1->GetScreenHeight();
    
    spriteSheet     = new Texture2D(renderer);
    timer           = new Timer();
    state           = new IdleState();
    
    collisionRect.x = static_cast<int>(PosX);
    collisionRect.y = static_cast<int>(PosY);
    collisionRect.w = 14;   // we don't need the whole frame (48x48), because
    collisionRect.h = 28;   // it's too big for our collision rect (hitbox)
    
    hitRect.x = 0;
    hitRect.y = 0;
    hitRect.w = 0;
    hitRect.h = 0;

    HP = 10000;
    PosX = 20;
    PosY = 155;
}

Player::~Player()
{
    delete spriteSheet;
    delete state;
    delete timer;
}

void Player::LoadContent()
{
    if (!spriteSheet->LoadFromFile("player.png"))
    {
        std::cout << "Failed to load player sprite sheet!" << std::endl;
    }
    else
    {
        // Idle Animation
        idleSpriteClips[0].x = 0;
        idleSpriteClips[0].y = 48;
        idleSpriteClips[0].w = 48;
        idleSpriteClips[0].h = 48;
        
        idleSpriteClips[1].x = 48;
        idleSpriteClips[1].y = 48;
        idleSpriteClips[1].w = 48;
        idleSpriteClips[1].h = 48;
        
        idleSpriteClips[2].x = 96;
        idleSpriteClips[2].y = 48;
        idleSpriteClips[2].w = 48;
        idleSpriteClips[2].h = 48;
        
        idleSpriteClips[3].x = 144;
        idleSpriteClips[3].y = 48;
        idleSpriteClips[3].w = 48;
        idleSpriteClips[3].h = 48;
        
        // Running animation
        runSpriteClips[0].x = 0;
        runSpriteClips[0].y = 0;
        runSpriteClips[0].w = 48;
        runSpriteClips[0].h = 48;
        
        runSpriteClips[1].x = 48;
        runSpriteClips[1].y = 0;
        runSpriteClips[1].w = 48;
        runSpriteClips[1].h = 48;
        
        runSpriteClips[2].x = 96;
        runSpriteClips[2].y = 0;
        runSpriteClips[2].w = 48;
        runSpriteClips[2].h = 48;
        
        runSpriteClips[3].x = 144;
        runSpriteClips[3].y = 0;
        runSpriteClips[3].w = 48;
        runSpriteClips[3].h = 48;
        
        // Kick animation
        kickSpriteClips[0].x = 0;
        kickSpriteClips[0].y = 96;
        kickSpriteClips[0].w = 48;
        kickSpriteClips[0].h = 48;
        
        kickSpriteClips[1].x = 48;
        kickSpriteClips[1].y = 96;
        kickSpriteClips[1].w = 48;
        kickSpriteClips[1].h = 48;
        
        kickSpriteClips[2].x = 96;
        kickSpriteClips[2].y = 96;
        kickSpriteClips[2].w = 48;
        kickSpriteClips[2].h = 48;
        
        kickSpriteClips[3].x = 144;
        kickSpriteClips[3].y = 96;
        kickSpriteClips[3].w = 48;
        kickSpriteClips[3].h = 48;
        
        // Punch animation
        punchSpriteClips[0].x = 0;
        punchSpriteClips[0].y = 144;
        punchSpriteClips[0].w = 48;
        punchSpriteClips[0].h = 48;
        
        punchSpriteClips[1].x = 48;
        punchSpriteClips[1].y = 144;
        punchSpriteClips[1].w = 48;
        punchSpriteClips[1].h = 48;
        
        punchSpriteClips[2].x = 96;
        punchSpriteClips[2].y = 144;
        punchSpriteClips[2].w = 48;
        punchSpriteClips[2].h = 48;
        
        punchSpriteClips[3].x = 144;
        punchSpriteClips[3].y = 144;
        punchSpriteClips[3].w = 48;
        punchSpriteClips[3].h = 48;
        
        // Jump animation
        jumpSpriteClips[0].x = 0;
        jumpSpriteClips[0].y = 192;
        jumpSpriteClips[0].w = 48;
        jumpSpriteClips[0].h = 48;
        
        jumpSpriteClips[1].x = 48;
        jumpSpriteClips[1].y = 192;
        jumpSpriteClips[1].w = 48;
        jumpSpriteClips[1].h = 48;
        
        jumpSpriteClips[2].x = 96;
        jumpSpriteClips[2].y = 192;
        jumpSpriteClips[2].w = 48;
        jumpSpriteClips[2].h = 48;
        
        jumpSpriteClips[3].x = 144;
        jumpSpriteClips[3].y = 192;
        jumpSpriteClips[3].w = 48;
        jumpSpriteClips[3].h = 48;
        
        // Jump kick
        jumpKickClip.x = 0;
        jumpKickClip.y = 240;
        jumpKickClip.w = 48;
        jumpKickClip.h = 48;
    }
}

void Player::Update(SDL_Event* e)
{
    event = e;
    
    double delta = timer->GetDelta();
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    state->HandleInput(*this, currentKeyStates, event);
    state->Update(*this, delta);
    
    collisionRect.x = static_cast<int>(PosX + 17);    // we don't need the whole frame (48x48), because
    collisionRect.y = static_cast<int>(PosY + 20);    // it's too big for our collision rect (hitbox)
    
    if (CurrentState == KICKING)
    {
        if (currentDirection == faceDirection::right)
        {
            hitRect.x = static_cast<int>(PosX + 36);
            hitRect.y = static_cast<int>(PosY + 25);
            hitRect.w = 5;
            hitRect.h = 5;
        }
        else if (currentDirection == faceDirection::left)
        {
            hitRect.x = static_cast<int>(PosX + 6);
            hitRect.y = static_cast<int>(PosY + 25);
            hitRect.w = 5;
            hitRect.h = 5;
        }
    }
    else if (CurrentState == PUNCHING)
    {
        if (currentDirection == faceDirection::right)
        {
            hitRect.x = static_cast<int>(PosX + 38);
            hitRect.y = static_cast<int>(PosY + 26);
            hitRect.w = 5;
            hitRect.h = 5;
        }
        else if (currentDirection == faceDirection::left)
        {
            hitRect.x = static_cast<int>(PosX + 6);
            hitRect.y = static_cast<int>(PosY + 26);
            hitRect.w = 5;
            hitRect.h = 5;
        }
    }
    else if (CurrentState == JUMPKICK)
    {
        if (currentDirection == faceDirection::right)
        {
            hitRect.x = static_cast<int>(PosX + 37);
            hitRect.y = static_cast<int>(PosY + 40);
            hitRect.w = 7;
            hitRect.h = 7;
        }
        else if (currentDirection == faceDirection::left)
        {
            hitRect.x = static_cast<int>(PosX + 5);
            hitRect.y = static_cast<int>(PosY + 40);
            hitRect.w = 7;
            hitRect.h = 7;
        }
    }
    else
    {
        hitRect.x = 0;
        hitRect.y = 0;
        hitRect.w = 0;
        hitRect.h = 0;
    }
}

void Player::Render()
{
    if (CurrentState == IDLE)
    {
        currentClip = &idleSpriteClips[frameToDraw];
        if (currentDirection == faceDirection::left)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip);
        }
        else if (currentDirection == faceDirection::right)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
    
    if (CurrentState == RUNNING)
    {
        currentClip = &runSpriteClips[frameToDraw];
        if (currentDirection == faceDirection::left)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else if (currentDirection == faceDirection::right)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
    
    if (CurrentState == KICKING)
    {
        currentClip = &kickSpriteClips[frameToDraw];
        if (currentDirection == faceDirection::left)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else if (currentDirection == faceDirection::right)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
        
        SDL_SetRenderDrawColor(renderer, 221, 76, 163, 255);
        SDL_RenderDrawRect(renderer, &hitRect);
    }
    
    if (CurrentState == PUNCHING)
    {
        currentClip = &punchSpriteClips[frameToDraw];
        if (currentDirection == faceDirection::left)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else if (currentDirection == faceDirection::right)
        {
            spriteSheet->Render((int)PosX, (int)PosY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
        
        SDL_SetRenderDrawColor(renderer, 221, 76, 163, 255);
        SDL_RenderDrawRect(renderer, &hitRect);
    }
    
    if (CurrentState == JUMPING)
    {
        currentClip = &jumpSpriteClips[frameToDraw];
        if (currentDirection == faceDirection::left)
        {
            spriteSheet->Render((int)PosX, (int)(PosY + posZ), currentClip, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else if (currentDirection == faceDirection::right)
        {
            spriteSheet->Render((int)PosX, (int)(PosY + posZ), currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
    
    if (CurrentState == JUMPKICK)
    {
        currentClip = &jumpKickClip;
        if (currentDirection == faceDirection::left)
        {
            spriteSheet->Render((int)PosX, (int)(PosY + posZ), currentClip, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else if (currentDirection == faceDirection::right)
        {
            spriteSheet->Render((int)PosX, (int)(PosY + posZ), currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
        
        SDL_SetRenderDrawColor(renderer, 221, 76, 163, 255);
        SDL_RenderDrawRect(renderer, &hitRect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
    SDL_RenderDrawRect(renderer, &collisionRect);
}

void Player::Move()
{
    // normalizing diagonal movement
    auto length = static_cast<float>(movementSpeed / (std::sqrt(std::pow(velX, 2) + std::pow(velY, 2))));

    if (velX != 0)
    {
        PosX += velX * length;
    }
    
    if (velY != 0)
    {
        PosY += velY * length;
    }

    if (velZ != 0)
    {
        posZ += velZ;
    }
}

void Player::Animate(double delta, int maxFrames)
{
    /* Delaying animation with delta time
     (https://gamedev.stackexchange.com/questions/44118/how-to-slow-down-a-sprite-that-updates-every-frame)
     Probably, something like this should be implemented in a global update */
    
    timeSinceLastFrame += delta;
    
    if (timeSinceLastFrame > animUpdateTime)
    {
        frameToDraw++;
        timeSinceLastFrame = 0;
    }
    
    if (frameToDraw >= maxFrames)
    {
        frameToDraw = 0;
    }
}

bool Player::Animating(int maxFrames)
{
    //std::cout << frameToDraw << std::endl;
    while (frameToDraw < maxFrames)
    {
        frameCount++;
        /* Magic number ftw! Basically, 20 makes sure that the animation has looped once,
         and when the frameToDraw equals 0 again, we break out of the animation cicle.
         Usually, animation returns to 0 around 35th frameCount, but can be less, so
         20 is a safe bet. If we use something less than 10, we might still be at our
         first zeroes of frameToDraw and then the loop will break too early. */
        if (frameCount > 20 && frameToDraw == 0)
            break;
        //std::cout << frameCount << " " << frameToDraw << std::endl;
        return true;
    }
    
    frameToDraw = 0;
    frameCount = 0;
    return false;
}

bool Player::DoDamage()
{
    target = level1->CurrentEnemy;

    if (target != nullptr)
    {
        /* get the current enemy who's collision rect collided with the player hit rect
         * lock that enemy while player do the damage and send him in a receiving damage state
         */

        if (CurrentState == PUNCHING)
        {
            target->SetHP(5);
            std::cout << target->GetHP() << std::endl;
            return true;
        }
        else if (CurrentState == KICKING)
        {
            target->SetHP(10);
            std::cout << target->GetHP() << std::endl;
            return true;
        }
    }
    else
    {
        std::cout << "Current enemy is null" << std::endl;
    }

    return false;
}

bool Player::ReceiveDamage()
{
    target = level1->CurrentEnemy;

    if (target != nullptr)
    {
        if (target->DoDamage())
        {
            spriteSheet->SetColor(255, 0, 0);

            return true;
        }
        else
        {
            spriteSheet->SetColor(255, 255, 255);

            return false;
        }
    }
    else
    {
        std::cout << "Current enemy is null" << std::endl;
    }

    return false;
}

const SDL_Rect Player::GetCollisionRect()
{
    return collisionRect;
}

const SDL_Rect Player::GetHitRect()
{
    return hitRect;
}

bool Player::CollidesUp()
{
    return level1->PlayerCollidesUp();
}

bool Player::CollidesRight()
{
    return level1->PlayerCollidesRight();
}

bool Player::CollidesDown()
{
    return level1->PlayerCollidesDown();
}

bool Player::CollidesLeft()
{
    return level1->PlayerCollidesLeft();
}

