//
//  Enemy_1.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "FatGangMember.hpp"
#include "../Screens/Level_1.hpp"

FatGangMember::FatGangMember(SDL_Renderer* r, Level_1* l1, int x, int y)
{
    renderer = r;
    level1 = l1;
    screenWidth = l1->GetScreenWidth();
    screenHeight = l1->GetScreenHeight();
    
    collisionRect.x = static_cast<int>(PosX);
    collisionRect.y = static_cast<int>(PosY);
    collisionRect.w = 14;
    collisionRect.h = 28;

    HP = 1050;
    PosX = x;
    PosY = y;

    spriteSheet = new Texture2D(renderer);
    timer = new Timer();
    state = new IdleState();
    
    LoadContent();
}

FatGangMember::~FatGangMember()
{
    delete spriteSheet;
    delete state;
    delete timer;
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

    FindNearestPlayer();

    state->HandleAction(*this, delta);
    state->Update(*this, delta);
    
    collisionRect.x = static_cast<int>(PosX + 17);    // we don't need the whole frame (48x48), because
    collisionRect.y = static_cast<int>(PosY + 20);    // it's too big for our collision rect (hitbox)

    if (CurrentState == State::ATTACKING)
    {
        if (CurrentDirection == FaceDirection::RIGHT)
        {
            hitRect.x = static_cast<int>(PosX + 36);
            hitRect.y = static_cast<int>(PosY + 25);
            hitRect.w = 5;
            hitRect.h = 5;
        }
        else if (CurrentDirection == FaceDirection::LEFT)
        {
            hitRect.x = static_cast<int>(PosX + 6);
            hitRect.y = static_cast<int>(PosY + 25);
            hitRect.w = 5;
            hitRect.h = 5;
        }
    }
}

void FatGangMember::Render(int camX)
{
    if (CurrentState == State::IDLE)
    {
        currentClip = &idleSpriteClips[FrameToDraw];
        if (CurrentDirection == FaceDirection::LEFT)
        {
            spriteSheet->Render(static_cast<int>(PosX) - camX, static_cast<int>(PosY), currentClip);
        }
        else if (CurrentDirection == FaceDirection::RIGHT)
        {
            spriteSheet->Render(static_cast<int>(PosX) - camX, static_cast<int>(PosY), currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }

    if (CurrentState == State::RUNNING)
    {
        currentClip = &runSpriteClips[FrameToDraw];
        if (CurrentDirection == FaceDirection::LEFT)
        {
            spriteSheet->Render(static_cast<int>(PosX) - camX, static_cast<int>(PosY), currentClip);
        }
        else if (CurrentDirection == FaceDirection::RIGHT)
        {
            spriteSheet->Render(static_cast<int>(PosX) - camX, static_cast<int>(PosY), currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }

    if (CurrentState == State::ATTACKING)
    {
        currentClip = &attackSpriteClips[FrameToDraw];
        if (CurrentDirection == FaceDirection::LEFT)
        {
            spriteSheet->Render(static_cast<int>(PosX) - camX, static_cast<int>(PosY), currentClip);
        }
        else if (CurrentDirection == FaceDirection::RIGHT)
        {
            spriteSheet->Render(static_cast<int>(PosX) - camX, static_cast<int>(PosY), currentClip, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }

//        SDL_SetRenderDrawColor(renderer, 221, 76, 163, 255);
//        SDL_RenderDrawRect(renderer, &hitRect);
    }

//    SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
//    SDL_RenderDrawRect(renderer, &collisionRect);
}

void FatGangMember::Move()
{
    // normalizing diagonal movement
    auto length = static_cast<float>(VELOCITY / (std::sqrt(std::pow(VelX, 2) + std::pow(VelY, 2))));

    if (VelX != 0)
    {
        PosX += VelX * length;
    }

    if (VelY != 0)
    {
        PosY += VelY * length;
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
        {
            AttackCounter++;
            break;
        }
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

void FatGangMember::FindNearestPlayer()
{
    target = level1->FindPlayer();
    PlayerAway = PosX > target->GetPosX() + 25 || PosX < target->GetPosX() - 23;
}

void FatGangMember::MoveToPlayer()
{
    if (PosX > target->GetPosX() + 25)
    {
        CurrentDirection = FaceDirection::LEFT;
        if (PosY > target->GetPosY() + 2)
        {
            VelX = -MovementSpeed;

            VelY = -MovementSpeed;
            if (PosY <= level1->GetLevelUpperCollider().y)
            {
                VelY = 0;
            }
        }
        else if (GetPosY() < target->GetPosY() - 2)
        {
            VelX = -MovementSpeed;

            VelY = MovementSpeed;
            if (PosY >= level1->GelLevelDownerCollider().y - level1->GelLevelDownerCollider().h)
            {
                VelY = 0;
            }
        }
        else
        {
            VelX = -MovementSpeed;
            VelY = 0;
        }
    }
    else if (PosX < target->GetPosX() - 5)
    {
        CurrentDirection = FaceDirection::RIGHT;
        if (GetPosY() > target->GetPosY() + 2)
        {
            VelX = MovementSpeed;

            VelY = -MovementSpeed;
            if (PosY <= level1->GetLevelUpperCollider().y)
            {
                VelY = 0;
            }
        }
        else if (PosY < target->GetPosY() - 2)
        {
            VelX = MovementSpeed;

            VelY = MovementSpeed;
            if (PosY >= level1->GelLevelDownerCollider().y - level1->GelLevelDownerCollider().h)
            {
                VelY = 0;
            }
        }
        else
        {
            VelX = MovementSpeed;
            VelY = 0;
        }
    }
    else
    {
        VelX = 0;
    }
}

void FatGangMember::MoveAwayFromPlayer()
{
    if (PosX < target->GetPosX() + 100)
    {
        VelX = MovementSpeed;

        if (PosY <= level1->GetLevelUpperCollider().y ||
            PosY >= level1->GelLevelDownerCollider().y - level1->GelLevelDownerCollider().h - 26)
        {
            VelY = 0;
        }
    }
    else if (PosX > target->GetPosX() - 100)
    {
        VelX = -MovementSpeed;

        if (PosY >= level1->GelLevelDownerCollider().y - level1->GelLevelDownerCollider().h)
        {
            VelY = 0;
        }
    }
    else
    {
        VelX = 0;
    }
}

void FatGangMember::AttackPlayer()
{
    if (!PlayerAway)
    {
        Attacking = true;
    }
}

bool FatGangMember::PlayerFarAway()
{
    target = level1->FindPlayer();

    if (target != nullptr)
    {
        return GetPosX() > target->GetPosX() + 70 || GetPosX() < target->GetPosX() - 70;
    }

    return true;
}

bool FatGangMember::DoDamage()
{
    target = level1->FindPlayer();

    if (target != nullptr)
    {
        if (CurrentState == State::ATTACKING)
        {
            target->SetHP(5);
            Attacking = true;

            return true;
        }

        Attacking = false;
    }
    else
    {
        std::cout << "target is null" << std::endl;
    }

    return false;
}

bool FatGangMember::ReceiveDamage()
{
    //target = level1->FindPlayer();

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
        std::cout << "target is null" << std::endl;
    }

    return false;
}
