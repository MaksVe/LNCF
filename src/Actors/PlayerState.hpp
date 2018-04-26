//
//  PlayerState.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/17/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef PlayerState_hpp
#define PlayerState_hpp

#include <SDL2/SDL.h>

class Player;

class PlayerState
{
public:
    virtual ~PlayerState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) {}
    virtual void Update(Player& player, double delta) {}
};



class IdleState : public PlayerState
{
public:
    IdleState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event);
    virtual void Update(Player& player, double delta);
};



class RunningState : public PlayerState
{
public:
    RunningState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event);
    virtual void Update(Player& player, double delta);
};



class KickingState : public PlayerState
{
public:
    KickingState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event);
    virtual void Update(Player& player, double delta);
};



class PunchingState : public PlayerState
{
public:
    PunchingState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event);
    virtual void Update(Player& player, double delta);
    
    bool linkingPunch = false;
};



class JumpingState : public PlayerState
{
public:
    JumpingState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event);
    virtual void Update(Player& player, double delta);
    
    float JumpVelocity = 10.0f;
};



#endif /* PlayerState_hpp */
