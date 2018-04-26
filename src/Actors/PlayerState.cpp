 //
//  PlayerState.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/17/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "PlayerState.hpp"

#include "Player.hpp"

// startposY will remember player current Y position to get the player back
// where he was after jumping.
float startPosY;

// ------------- idle state ------------- //
void IdleState::HandleInput(Player &player, const Uint8* keyState, SDL_Event* event)
{
    player.velX = 0;
    player.velY = 0;
    
    if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_RIGHT] ||
        keyState[SDL_SCANCODE_UP]   || keyState[SDL_SCANCODE_DOWN])
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
        if (event->key.keysym.sym == SDLK_h)
        {
            player.CurrentState = player.KICKING;
            player.frameToDraw = 0;
            if (player.state != nullptr)
            {
                delete player.state;
                player.state = new KickingState();
            }
        }
        else if (event->key.keysym.sym == SDLK_g)
        {
            player.CurrentState = player.PUNCHING;
            player.frameToDraw = 0;
            if (player.state != nullptr)
            {
                delete player.state;
                player.state = new PunchingState();
            }
        }
        else if (event->key.keysym.sym == SDLK_SPACE)
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
// ------------- idle state ------------- //



// ------------- running state ------------- //
void RunningState::HandleInput(Player &player, const Uint8* keyState, SDL_Event* event)
{
    if (keyState[SDL_SCANCODE_LEFT])
    {
        player.currentDirection = Player::faceDirection::left;
        
        if (keyState[SDL_SCANCODE_UP])
        {
            player.velX = -player.movementSpeed;
            player.velY = -player.movementSpeed;
        }
        else if (keyState[SDL_SCANCODE_DOWN])
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
                if (event->key.keysym.sym == SDLK_SPACE)
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
    else if (keyState[SDL_SCANCODE_RIGHT])
    {
        player.currentDirection = Player::faceDirection::right;
        
        if (keyState[SDL_SCANCODE_UP])
        {
            player.velX = player.movementSpeed;
            player.velY = -player.movementSpeed;
        }
        else if (keyState[SDL_SCANCODE_DOWN])
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
                if (event->key.keysym.sym == SDLK_SPACE)
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
    else if (keyState[SDL_SCANCODE_UP])
    {
        player.velY = -player.movementSpeed;
        player.velX = 0;
    }
    else if(keyState[SDL_SCANCODE_DOWN])
    {
        player.velY = player.movementSpeed;
        player.velX = 0;
    }
    else if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (event->key.keysym.sym == SDLK_SPACE)
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
