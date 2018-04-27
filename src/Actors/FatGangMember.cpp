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

    spriteSheet = new Texture2D(renderer);
    timer = new Timer();
    state = new IdleState();
    
    LoadContent();
}

FatGangMember::~FatGangMember()
{
    delete spriteSheet;
    delete state;
}

void FatGangMember::LoadContent()
{
    if (!spriteSheet->LoadFromFile("foes.png"))
    {
        std::cout << "Failed to load player sprite sheet!" << std::endl;
    }
    else
    {
        // Idle and Running Animation
        idleSpriteClips[0].x = runSpriteClips[0].x = 0;
        idleSpriteClips[0].y = runSpriteClips[0].y = 0;
        idleSpriteClips[0].w = runSpriteClips[0].w = 48;
        idleSpriteClips[0].h = runSpriteClips[0].h = 48;

        idleSpriteClips[1].x = runSpriteClips[1].x = 48;
        idleSpriteClips[1].y = runSpriteClips[1].y = 0;
        idleSpriteClips[1].w = runSpriteClips[1].w = 48;
        idleSpriteClips[1].h = runSpriteClips[1].h = 48;

        idleSpriteClips[2].x = runSpriteClips[2].x = 96;
        idleSpriteClips[2].y = runSpriteClips[2].y = 0;
        idleSpriteClips[2].w = runSpriteClips[2].w = 48;
        idleSpriteClips[2].h = runSpriteClips[2].h = 48;

        idleSpriteClips[3].x = runSpriteClips[3].x = 144;
        idleSpriteClips[3].y = runSpriteClips[3].y = 0;
        idleSpriteClips[3].w = runSpriteClips[3].w = 48;
        idleSpriteClips[3].h = runSpriteClips[3].h = 48;

        // Attacking Animation
        attackSpriteClips[0].x = 0;
        attackSpriteClips[0].y = 48;
        attackSpriteClips[0].w = 48;
        attackSpriteClips[0].h = 48;

        attackSpriteClips[1].x = 48;
        attackSpriteClips[1].y = 48;
        attackSpriteClips[1].w = 48;
        attackSpriteClips[1].h = 48;

        attackSpriteClips[2].x = 96;
        attackSpriteClips[2].y = 48;
        attackSpriteClips[2].w = 48;
        attackSpriteClips[2].h = 48;
    }
}

void FatGangMember::Update(SDL_Event *e)
{
    event = e;
    double delta = timer->GetDelta();

    state->HandleAction(*this, delta);
    state->Update(*this, delta);
    
    collisionRect.x = posX + 17;    // we don't need the whole frame (48x48), because
    collisionRect.y = posY + 20;    // it's too big for our collision rect (hitbox)

    if (CurrentState == State::ATTACKING)
    {
        if (CurrentDirection == FaceDirection::RIGHT)
        {
            hitRect.x = posX + 36;
            hitRect.y = posY + 25;
            hitRect.w = 5;
            hitRect.h = 5;
        }
        else if (CurrentDirection == FaceDirection::LEFT)
        {
            hitRect.x = posX + 6;
            hitRect.y = posY + 25;
            hitRect.w = 5;
            hitRect.h = 5;
        }
    }
}

void FatGangMember::Render()
{
    if (CurrentState == State::IDLE)
    {
        currentClip = &idleSpriteClips[FrameToDraw];
        if (CurrentDirection == FaceDirection::LEFT)
        {
            spriteSheet->Render(posX, posY, currentClip);
        }
        else if (CurrentDirection == FaceDirection::RIGHT)
        {
            spriteSheet->Render(posX, posY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }

    if (CurrentState == State::RUNNING)
    {
        currentClip = &runSpriteClips[FrameToDraw];
        if (CurrentDirection == FaceDirection::LEFT)
        {
            spriteSheet->Render(posX, posY, currentClip);
        }
        else if (CurrentDirection == FaceDirection::RIGHT)
        {
            spriteSheet->Render(posX, posY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }

    if (CurrentState == State::ATTACKING)
    {
        currentClip = &attackSpriteClips[FrameToDraw];
        if (CurrentDirection == FaceDirection::LEFT)
        {
            spriteSheet->Render(posX, posY, currentClip);
        }
        else if (CurrentDirection == FaceDirection::RIGHT)
        {
            spriteSheet->Render(posX, posY, currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
#ifdef DEBUG
        SDL_SetRenderDrawColor(renderer, 221, 76, 163, 255);
        SDL_RenderDrawRect(renderer, &hitRect);
#endif
    }
#ifdef DEBUG
    SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
    SDL_RenderDrawRect(renderer, &collisionRect);
#endif
}

void FatGangMember::Move()
{
    // normalizing diagonal movement
    float length = VELOCITY / (std::sqrt(std::pow(VelX, 2) + std::pow(VelY, 2)));

    if (VelX != 0)
    {
        posX += VelX * length;
    }

    if (VelY != 0)
    {
        posY += VelY * length;
    }
}

void FatGangMember::Animate(double delta, int maxFrames)
{
    /* Delaying animation with delta time
     (https://gamedev.stackexchange.com/questions/44118/how-to-slow-down-a-sprite-that-updates-every-frame)
     Probably, something like this should be implemented in a global update */

    timeSinceLastFrame += delta;

    if (timeSinceLastFrame > animUpdateTime)
    {
        FrameToDraw++;
        timeSinceLastFrame = 0;
    }

    if (FrameToDraw >= maxFrames)
    {
        FrameToDraw = 0;
    }
}

bool FatGangMember::Animating(int maxFrames)
{
    //std::cout << frameToDraw << std::endl;
    while (FrameToDraw < maxFrames)
    {
        FrameCount++;
        /* Magic number ftw! Basically, 20 makes sure that the animation has looped once,
         and when the frameToDraw equals 0 again, we break out of the animation cicle.
         Usually, animation returns to 0 around 35th frameCount, but can be less, so
         20 is a safe bet. If we use something less than 10, we might still be at our
         first zeroes of frameToDraw and then the loop will break too early. */
        if (FrameCount > 20 && FrameToDraw == 0)
            break;
        //std::cout << frameCount << " " << frameToDraw << std::endl;
        return true;
    }

    FrameToDraw = 0;
    FrameCount = 0;
    return false;
}

const SDL_Rect FatGangMember::GetCollisionRect()
{
    return collisionRect;
}

const SDL_Rect FatGangMember::GetHitRect()
{
    return hitRect;
}
