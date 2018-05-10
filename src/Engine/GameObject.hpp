//
// Created by Максим on 5/10/18.
//

#pragma once


class GameObject
{
public:
    virtual ~GameObject() {}

    virtual void Render() {}

    virtual float GetPosY() { return PosY; }
    virtual float GetPosX() { return PosX; }

protected:
    float PosY{};
    float PosX{};
};
