//
//  Actor.h
//  sdl_brawler_mac
//
//  Created by Максим on 4/24/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <memory>
#include "../Engine/GameObject.hpp"
#include "ActorState.hpp"

class Actor : public virtual GameObject
{
public:
    virtual ~Actor()                            {}

    virtual const SDL_Rect GetCollisionRect()   = 0;
    virtual const SDL_Rect GetHitRect()         = 0;

    virtual bool DoDamage()                     = 0;
    virtual bool ReceiveDamage()                = 0;

    virtual int GetHP()                         { return HP; }
    virtual void SetHP(int amountOfDamage)      { HP = HP - amountOfDamage; }

    virtual ActorState* GetState()                                      { return state; }
    virtual void SetState(ActorState* actorState)   { delete state; state = actorState; }

protected:
    int HP{};
    ActorState* state;
};
