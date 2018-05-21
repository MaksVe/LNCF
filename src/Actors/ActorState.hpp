//
//  ActorState.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/17/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <iostream>
#include "SDL.h"

class Player;

class ActorState
{
public:
    virtual ~ActorState() {}

    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) {}
    virtual void Update(Player& player, double delta) {}
};

class IdleState : public ActorState
{
public:
    IdleState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
};

class RunningState : public ActorState
{
public:
    RunningState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
};

class KickingState : public ActorState
{
public:
    KickingState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
};

class PunchingState : public ActorState
{
public:
    PunchingState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
};

class JumpingState : public ActorState
{
public:
    JumpingState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;

    float JumpVelocity = 1.1f;
};

class StaggeredState : public ActorState
{
public:
    StaggeredState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
};
