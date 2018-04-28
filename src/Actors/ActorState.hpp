//
//  ActorState.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/17/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef PlayerState_hpp
#define PlayerState_hpp

#include <iostream>
#include <SDL2/SDL.h>

class Player;
class FatGangMember;

class ActorState
{
public:
    virtual ~ActorState() {}
    
    virtual void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) {}
    virtual void Update(Player& player, double delta) {}
    virtual void HandleAction(FatGangMember& gangMemberA, double delta) {}
    virtual void Update(FatGangMember& gangMemberA, double delta) {}
};



class IdleState : public ActorState
{
public:
    IdleState() {}
    
    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
    void HandleAction(FatGangMember& gangMemberA, double delta) override;
    void Update(FatGangMember& gangMemberA, double delta) override;
};



class RunningState : public ActorState
{
public:
    RunningState() {}
    
    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
    void HandleAction(FatGangMember& gangMemberA, double delta) override;
    void Update(FatGangMember& gangMemberA, double delta) override;
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
    
    bool linkingPunch = false;
};



class JumpingState : public ActorState
{
public:
    JumpingState() {}

    void HandleInput(Player& player, const Uint8* keyState, SDL_Event* event) override;
    void Update(Player& player, double delta) override;
    
    float JumpVelocity = 10.0f;
};

class AttackingState : public ActorState
{
public:
    AttackingState() {}

    void HandleAction(FatGangMember& gangMemberA, double delta) override;
    void Update(FatGangMember& gangMemberA, double delta) override;
};



#endif /* PlayerState_hpp */
