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
            player.SetState(new RunningState);
        }
    }
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (keyState[SDL_SCANCODE_H])
        {
            player.CurrentState = player.KICKING;
            player.frameToDraw = 0;
            if (player.GetState() != nullptr)
            {
                player.SetState(new KickingState);
            }
        }
        else if (keyState[SDL_SCANCODE_G])
        {
            player.CurrentState = player.PUNCHING;
            player.frameToDraw = 0;
            if (player.GetState() != nullptr)
            {
                player.SetState(new PunchingState);
            }
        }
        else if (keyState[SDL_SCANCODE_SPACE])
        {
            player.CurrentState = player.JUMPING;
            player.frameToDraw = 0;
            if (player.GetState() != nullptr)
            {
                player.SetState(new JumpingState);
                startPosZ = 0;
            }
        }
    }
}

void IdleState::Update(Player &player, double delta)
{
    player.Animate(delta, Player::IDLE_FRAMES);
}



void IdleState::HandleAction(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Attacking = false;

    gangMemberA.FindNearestPlayer();
    if (gangMemberA.PlayerAway)
    {
        gangMemberA.CurrentState = FatGangMember::State::RUNNING;
        if (gangMemberA.GetState() != nullptr)
        {
            gangMemberA.SetState(new RunningState);
        }
    }
    else if (!gangMemberA.PlayerAway && !gangMemberA.Attacking)
    {
        gangMemberA.CurrentState = FatGangMember::State::ATTACKING;
        if (gangMemberA.GetState() != nullptr)
        {
            gangMemberA.SetState(new AttackingState);
        }
    }
}

void IdleState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Animate(delta, FatGangMember::IDLE_FRAMES);
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
                        player.SetState(new JumpingState);
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
                        player.SetState(new JumpingState);
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
                player.SetState(new JumpingState);
                startPosZ = 0;
            }
        }
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState);
        }
    }
}

void RunningState::Update(Player &player, double delta)
{
    player.Move();
    player.Animate(delta, Player::RUN_FRAMES);
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
            if (gangMemberA.GetState() != nullptr)
            {
                gangMemberA.SetState(new IdleState);
            }
        }
    }
    else
    {
        gangMemberA.MoveToPlayer();

        if (!gangMemberA.PlayerAway)
        {
            gangMemberA.CurrentState = FatGangMember::State::IDLE;
            if (gangMemberA.GetState() != nullptr)
            {
                gangMemberA.SetState(new IdleState);
            }
        }
    }
}

void RunningState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Move();
    gangMemberA.Animate(delta, FatGangMember::RUN_FRAMES);
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
            player.SetState(new IdleState);
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
                    player.SetState(new IdleState);
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
            player.SetState(new IdleState);
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
                //player.posZ = 0;
                std::cout << startPosZ << " " << player.posZ << " " << player.GetPosY() << std::endl;
            }
        }
    }
    else
    {
        player.CurrentState = player.IDLE;
        if (player.GetState() != nullptr)
        {
            player.SetState(new IdleState);
        }
    }
}

void JumpingState::Update(Player &player, double delta)
{
    player.Move();
    player.Animate(delta, Player::JUMP_FRAMES);
}
// ------------- jumping state ------------- //



// ------------- attacking state ------------- //
void AttackingState::HandleAction(FatGangMember &gangMemberA, double delta)
{
    if (gangMemberA.Animating(FatGangMember::ATTACK_FRAMES))
    {
        // Attack
        gangMemberA.Attacking = true;
        if (gangMemberA.AttackCounter >= 1)
        {
            std::cout << "Attacked once" << std::endl;
            gangMemberA.CurrentState = FatGangMember::State::RUNNING;
            gangMemberA.FrameToDraw = 0;
            if (gangMemberA.GetState() != nullptr)
            {
                gangMemberA.SetState(new RunningState);
            }
        }
    }
    else
    {
        gangMemberA.CurrentState = FatGangMember::State::IDLE;
        if (gangMemberA.GetState() != nullptr)
        {
            gangMemberA.SetState(new IdleState);
        }
    }
}

void AttackingState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.Animate(delta, FatGangMember::ATTACK_FRAMES);
}
// ------------- attacking state ------------- //



// ------------- staggered state ------------- //
void StaggeredState::HandleInput(Player& player, const Uint8* keyState, SDL_Event* event)
{
    player.CurrentState = player.IDLE;
    if (player.GetState() != nullptr)
    {
        player.SetState(new IdleState);
    }
}

void StaggeredState::Update(Player &player, double delta)
{
    //player.ReceiveDamage();
    player.Animate(delta, Player::IDLE_FRAMES);
}



void StaggeredState::HandleAction(FatGangMember &gangMemberA, double delta)
{
    if (gangMemberA.Animating(FatGangMember::IDLE_FRAMES))
    {
        // receiving damage
    }
    else
    {
        gangMemberA.CurrentState = FatGangMember::State::IDLE;
        if (gangMemberA.GetState() != nullptr)
        {
            gangMemberA.SetState(new IdleState);
        }
    }
}

void StaggeredState::Update(FatGangMember &gangMemberA, double delta)
{
    gangMemberA.ReceiveDamage();
    gangMemberA.Animate(delta, FatGangMember::IDLE_FRAMES);
}
// ------------- staggered state ------------- //