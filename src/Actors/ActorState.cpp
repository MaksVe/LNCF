 //
//  ActorState.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/17/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "ActorState.hpp"
#include "Player.hpp"

// startposY will remember player current Y position to get the player back
// where he was after jumping.
float startPosZ;

// ------------- idle state ------------- //
void IdleState::HandleInput(Player &player, const Uint8* keyState, SDL_Event* event)
{
    player.velX = 0;
    player.velY = 0;
    
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_S] ||
        keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D])
    {
        player.CurrentState = player.RUNNING;
        if (player.GetState() != nullptr)
        {
            player.SetState(new RunningState());
        }
    }
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (keyState[SDL_SCANCODE_H])
        {
            player.frameToDraw = 0;
            player.CurrentState = player.KICKING;

            if (player.GetState() != nullptr)
            {
                player.SetState(new KickingState());
            }
        }
        else if (keyState[SDL_SCANCODE_G])
        {
            player.frameToDraw = 0;
            player.CurrentState = player.PUNCHING;

            if (player.GetState() != nullptr)
            {
                player.SetState(new PunchingState());
            }
        }
        else if (keyState[SDL_SCANCODE_SPACE])
        {
            player.frameToDraw = 0;
            player.CurrentState = player.JUMPING;

            if (player.GetState() != nullptr)
            {
                player.SetState(new JumpingState());
                startPosZ = 0;
            }
        }
    }
}

void IdleState::Update(Player &player, double delta)
{
    player.Animate(delta, Player::IDLE_FRAMES);
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
            player.velX = -Player::movementSpeed;
            if (player.CollidesLeft())
            {
                std::cout << "collides left" << std::endl;
                player.velX = 0;
            }

            player.velY = -Player::movementSpeed;
            if (player.CollidesUp())
            {
                std::cout << "collides up" << std::endl;
                player.velY = 0;
            }
        }
        else if (keyState[SDL_SCANCODE_S])
        {
            player.velX = -Player::movementSpeed;
            if (player.CollidesLeft())
            {
                player.velX = 0;
            }

            player.velY = Player::movementSpeed;
            if (player.CollidesDown())
            {
                player.velY = 0;
            }
        }
        else
        {
            player.velX = -Player::movementSpeed;
            if (player.CollidesLeft())
            {
                player.velX = 0;
            }
            player.velY = 0;
            
            if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
            {
                if (keyState[SDL_SCANCODE_SPACE])
                {
                    player.CurrentState = player.JUMPING;
                    player.frameToDraw = 0;
                    if (player.GetState() != nullptr)
                    {
                        player.SetState(new JumpingState());
                        startPosZ = 0;
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
            player.velX = Player::movementSpeed;
            if (player.CollidesRight())
            {
                player.velX = 0;
            }

            player.velY = -Player::movementSpeed;
            if (player.CollidesUp())
            {
                player.velY = 0;
            }
        }
        else if (keyState[SDL_SCANCODE_S])
        {
            player.velX = Player::movementSpeed;
            if (player.CollidesRight())
            {
                player.velX = 0;
            }
            player.velY = Player::movementSpeed;
            if (player.CollidesDown())
            {
                player.velY = 0;
            }
        }
        else
        {
            player.velX = Player::movementSpeed;
            if (player.CollidesRight())
            {
                player.velX = 0;
            }
            player.velY = 0;
            
            if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
            {
                if (keyState[SDL_SCANCODE_SPACE])
                {
                    player.CurrentState = player.JUMPING;
                    player.frameToDraw = 0;
                    if (player.GetState() != nullptr)
                    {
                        player.SetState(new JumpingState());
                        startPosZ = 0;
                    }
                }
            }
        }
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        player.velY = -Player::movementSpeed;
        if (player.CollidesUp())
        {
            player.velY = 0;
        }
        player.velX = 0;
    }
    else if(keyState[SDL_SCANCODE_S])
    {
        player.velY = Player::movementSpeed;
        if (player.CollidesDown())
        {
            player.velY = 0;
        }
        player.velX = 0;
    }
    else if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (keyState[SDL_SCANCODE_SPACE])
        {
            player.CurrentState = player.JUMPING;
            player.frameToDraw = 0;
            if (player.GetState() != nullptr)
            {
                player.SetState(new JumpingState());
                startPosZ = 0;
            }
        }
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState());
        }
    }
}

void RunningState::Update(Player &player, double delta)
{
    player.Move();
    player.Animate(delta, Player::RUN_FRAMES);
}
// ------------- running state ------------- //



// ------------- kicking state ------------- //
void KickingState::HandleInput(Player &player, const Uint8 *keyState, SDL_Event* event)
{
    if (player.Animating(Player::KICK_FRAMES))
    {
        // wait animation to finish
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState());
        }
    }
}

void KickingState::Update(Player &player, double delta)
{
    player.Animate(delta, Player::KICK_FRAMES);
}
// ------------- kicking state ------------- //



// ------------- punching state ------------- //
void PunchingState::HandleInput(Player &player, const Uint8 *keyState, SDL_Event* event)
{
    if (player.Animating(Player::PUNCH_FRAMES))
    {
        if (player.frameToDraw >= 2)
        {
            if (keyState[SDL_SCANCODE_F])
            {
                if (player.frameToDraw > 2)
                {
//                    std::cout << "Continue animation to the second punch (kinda combo/link... :P)" << std::endl;
                    // combo activated, make more damage
                    player.LinkingPunch = true;
                }
            }
            else
            {
//                std::cout << "Stop punching, ignore the second punch from the sprite sheet" << std::endl;
                player.CurrentState = player.IDLE;
                if (player.GetState() != nullptr)
                {
                    player.SetState(new IdleState());
                }
            }
        }
    }
    else
    {
        player.LinkingPunch = false;
        player.CurrentState = player.IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState());
        }
    }
}

void PunchingState::Update(Player &player, double delta)
{
    player.Animate(delta, Player::PUNCH_FRAMES);
}
// ------------- punching state ------------- //



// ------------- jumping state ------------- //
void JumpingState::HandleInput(Player &player, const Uint8 *keyState, SDL_Event* event)
{
    if (player.Animating(Player::JUMP_FRAMES))
    {
        /* This method isn't the optimal way to do the jump. Actually,
         it's an absolute bullshit. But it'll work for now. */
        

        if (player.frameToDraw == 0 || player.frameToDraw == 1)
        {
            player.velZ = -JumpVelocity;
            
            std::cout << startPosZ << " " << player.posZ << player.GetPosY() << std::endl;
            
            // draw jumpkick
            if (keyState[SDL_SCANCODE_H])
            {
                player.CurrentState = player.JUMPKICK;
            }
        }
        else if (player.frameToDraw == 2 || player.frameToDraw == 3)
        {
            player.velZ = JumpVelocity;

            if (player.posZ >= startPosZ)
            {
                player.velZ = 0; // don't go over the start Y position
                player.posZ = 0;
                std::cout << startPosZ << " " << player.posZ << " " << player.GetPosY() << std::endl;
            }
        }
    }
    else
    {
        player.posZ = 0;
        player.CurrentState = player.IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState());
        }
    }
}

void JumpingState::Update(Player &player, double delta)
{
    player.Move();
    player.Animate(delta, Player::JUMP_FRAMES);
}
// ------------- jumping state ------------- //



// ------------- staggered state ------------- //
void StaggeredState::HandleInput(Player& player, const Uint8* keyState, SDL_Event* event)
{
    player.CurrentState = player.IDLE;
    if (player.Animating(Player::IDLE_FRAMES))
    {

    }
    else
    {
        player.posZ = 0;
        player.CurrentState = Player::IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState());
        }
    }
}

void StaggeredState::Update(Player &player, double delta)
{
    player.ReceiveDamage();
    player.Animate(delta, Player::IDLE_FRAMES);
}
// ------------- staggered state ------------- //