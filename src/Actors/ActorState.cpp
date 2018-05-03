 //
//  ActorState.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/17/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "ActorState.hpp"
#include "Player.hpp"
#include "FatGangMember.hpp"

// startposY will remember player current Y position to get the player back
// where he was after jumping.
float startPosY;

// ------------- idle state ------------- //
void IdleState::HandleInput(Player &player, const Uint8* keyState, SDL_Event* event)
{
    player.velX = 0;
    player.velY = 0;
    
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_S] ||
        keyState[SDL_SCANCODE_A]   || keyState[SDL_SCANCODE_D])
    {
        player.CurrentState = player.RUNNING;
        if (player.state != nullptr)
        {
            delete player.state;
            player.state = new RunningState();
        }
    }
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (keyState[SDL_SCANCODE_H])
        {
            player.CurrentState = player.KICKING;
            player.frameToDraw = 0;
            if (player.state != nullptr)
            {
                delete player.state;
                player.state = new KickingState();
            }
        }
        else if (keyState[SDL_SCANCODE_G])
        {
            player.CurrentState = player.PUNCHING;
            player.frameToDraw = 0;
            if (player.state != nullptr)
            {
                delete player.state;
                player.state = new PunchingState();
            }
        }
        else if (keyState[SDL_SCANCODE_SPACE])
        {
            player.CurrentState = player.JUMPING;
            player.frameToDraw = 0;
            if (player.state != nullptr)
            {
                delete player.state;
                player.state = new JumpingState();
                startPosY = player.posY;
            }
        }
    }
}

void IdleState::Update(Player &player, double delta)
{
    player.Animate(delta, player.IDLE_FRAMES);
}



void IdleState::HandleAction(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Attacking = false;

    gangMemberA.FindNearestPlayer();
    if (gangMemberA.PlayerAway)
    {
        gangMemberA.CurrentState = FatGangMember::State::RUNNING;
        if (gangMemberA.state != nullptr)
        {
            delete gangMemberA.state;
            gangMemberA.state = new RunningState();
        }
    }
    else if (!gangMemberA.PlayerAway && !gangMemberA.Attacking)
    {
        gangMemberA.CurrentState = FatGangMember::State::ATTACKING;
        if (gangMemberA.state != nullptr)
        {
            delete gangMemberA.state;
            gangMemberA.state = new AttackingState();
        }
    }
}

void IdleState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Animate(delta, gangMemberA.IDLE_FRAMES);
}
// ------------- idle state ------------- //



// ------------- running state ------------- //
void RunningState::HandleInput(Player &player, const Uint8* keyState, SDL_Event* event)
{
    if (keyState[SDL_SCANCODE_A])
    {
        player.currentDirection = Player::faceDirection::left;
        
        if (keyState[SDL_SCANCODE_W])
        {
            player.velX = -player.movementSpeed;
            player.velY = -player.movementSpeed;
        }
        else if (keyState[SDL_SCANCODE_S])
        {
            player.velX = -player.movementSpeed;
            player.velY = player.movementSpeed;
        }
        else
        {
            player.velX = -player.movementSpeed;
            player.velY = 0;
            
            if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
            {
                if (keyState[SDL_SCANCODE_SPACE])
                {
                    player.CurrentState = player.JUMPING;
                    player.frameToDraw = 0;
                    if (player.state != nullptr)
                    {
                        delete player.state;
                        player.state = new JumpingState();
                        startPosY = player.posY;
                    }
                }
            }
        }
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        player.currentDirection = Player::faceDirection::right;
        
        if (keyState[SDL_SCANCODE_W])
        {
            player.velX = player.movementSpeed;
            player.velY = -player.movementSpeed;
        }
        else if (keyState[SDL_SCANCODE_S])
        {
            player.velX = player.movementSpeed;
            player.velY = player.movementSpeed;
        }
        else
        {
            player.velX = player.movementSpeed;
            player.velY = 0;
            
            if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
            {
                if (keyState[SDL_SCANCODE_SPACE])
                {
                    player.CurrentState = player.JUMPING;
                    player.frameToDraw = 0;
                    if (player.state != nullptr)
                    {
                        delete player.state;
                        player.state = new JumpingState();
                        startPosY = player.posY;
                    }
                }
            }
        }
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        player.velY = -player.movementSpeed;
        player.velX = 0;
    }
    else if(keyState[SDL_SCANCODE_S])
    {
        player.velY = player.movementSpeed;
        player.velX = 0;
    }
    else if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (keyState[SDL_SCANCODE_SPACE])
        {
            player.CurrentState = player.JUMPING;
            player.frameToDraw = 0;
            if (player.state != nullptr)
            {
                delete player.state;
                player.state = new JumpingState();
                startPosY = player.posY;
            }
        }
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.state != nullptr)
        {
            delete player.state;
            player.state = new IdleState();
        }
    }
}

void RunningState::Update(Player &player, double delta)
{
    player.Move();
    player.Animate(delta, player.RUN_FRAMES);
}



void RunningState::HandleAction(FatGangMember &gangMemberA, double delta)
{
    if (gangMemberA.AttackCounter >= 1)
    {
        gangMemberA.MoveAwayFromPlayer();

        if (gangMemberA.PlayerFarAway())
        {
            gangMemberA.AttackCounter = 0;
            gangMemberA.CurrentState = FatGangMember::State::IDLE;
            if (gangMemberA.state != nullptr)
            {
                delete gangMemberA.state;
                gangMemberA.state = new IdleState();
            }
        }
    }
    else
    {
        gangMemberA.MoveToPlayer();

        if (!gangMemberA.PlayerAway)
        {
            gangMemberA.CurrentState = FatGangMember::State::IDLE;
            if (gangMemberA.state != nullptr)
            {
                delete gangMemberA.state;
                gangMemberA.state = new IdleState();
            }
        }
    }
}

void RunningState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Move();
    gangMemberA.Animate(delta, gangMemberA.RUN_FRAMES);
}
// ------------- running state ------------- //



// ------------- kicking state ------------- //
void KickingState::HandleInput(Player &player, const Uint8 *keyState, SDL_Event* event)
{
    if (player.Animating(player.KICK_FRAMES))
    {
        // wait animation to finish
        // put some kicking logic here?
        
        /* TODO: Create a kickingHitRect, binding it to the leg.
         Binding: animation frames are static, we just have to calculate x/y once
         and move the rectangle accordingly (magic numbers).
         If it ever meets another rectangle:
         if it meets enemy collision rectangle -> do damage
         if it meets game object -> if game object is destructible -> do damage
         */
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.state != nullptr)
        {
            delete player.state;
            player.state = new IdleState();
        }
    }
}

void KickingState::Update(Player &player, double delta)
{
    player.Animate(delta, player.KICK_FRAMES);
}
// ------------- kicking state ------------- //



// ------------- punching state ------------- //
void PunchingState::HandleInput(Player &player, const Uint8 *keyState, SDL_Event* event)
{
    if (player.Animating(player.PUNCH_FRAMES))
    {
        if (player.frameToDraw >= 2)
        {
            if (keyState[SDL_SCANCODE_F])
            {
                if (player.frameToDraw > 2)
                {
//                    std::cout << "Continue animation to the second punch (kinda combo/link... :P)" << std::endl;
                    // combo activated, make more damage
                    linkingPunch = true;
                }
            }
            else
            {
//                std::cout << "Stop punching, ignore the second punch from the sprite sheet" << std::endl;
                player.CurrentState = player.IDLE;
                if (player.state != nullptr)
                {
                    delete player.state;
                    player.state = new IdleState();
                }
            }
        }
    }
    else
    {
        linkingPunch = false;
        player.CurrentState = player.IDLE;
        if (player.state != nullptr)
        {
            delete player.state;
            player.state = new IdleState();
        }
    }
}

void PunchingState::Update(Player &player, double delta)
{
    player.Animate(delta, player.PUNCH_FRAMES);
}
// ------------- punching state ------------- //



// ------------- jumping state ------------- //
void JumpingState::HandleInput(Player &player, const Uint8 *keyState, SDL_Event* event)
{
    if (player.Animating(player.JUMP_FRAMES))
    {
        /* This method isn't the optimal way to do the jump. Actually,
         it's an absolute bullshit. But it'll work for now. */
        

        if (player.frameToDraw == 0 || player.frameToDraw == 1)
        {
            player.velY = -JumpVelocity;
            
//            std::cout << startPosY << " " << player.posY << std::endl;
            
            // draw jumpkick
            if (keyState[SDL_SCANCODE_H])
            {
                player.CurrentState = player.JUMPKICK;
            }
        }
        else if (player.frameToDraw == 2 || player.frameToDraw == 3)
        {
            player.velY = JumpVelocity;

            if (player.posY == startPosY)
            {
                player.velY = 0; // don't go over the start Y position
                
//                std::cout << startPosY << " " << player.posY << std::endl;
            }
        }
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.state != nullptr)
        {
            delete player.state;
            player.state = new IdleState();
        }
    }
}

void JumpingState::Update(Player &player, double delta)
{
    player.Move();
    player.Animate(delta, player.JUMP_FRAMES);
}
// ------------- jumping state ------------- //



// ------------- attacking state ------------- //
void AttackingState::HandleAction(FatGangMember &gangMemberA, double delta)
{
    if (gangMemberA.Animating(gangMemberA.ATTACK_FRAMES))
    {
        // Attack
        gangMemberA.Attacking = true;
        if (gangMemberA.AttackCounter >= 1)
        {
            std::cout << "Attacked once" << std::endl;
            gangMemberA.CurrentState = FatGangMember::State::RUNNING;
            gangMemberA.FrameToDraw = 0;
            if (gangMemberA.state != nullptr)
            {
                delete gangMemberA.state;
                gangMemberA.state = new RunningState();
            }
        }
    }
    else
    {
        gangMemberA.CurrentState = FatGangMember::State::IDLE;
        if (gangMemberA.state != nullptr)
        {
            delete gangMemberA.state;
            gangMemberA.state = new IdleState();
        }
    }
}

void AttackingState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Animate(delta, gangMemberA.ATTACK_FRAMES);
}
// ------------- attacking state ------------- //
