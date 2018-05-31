//
// Created by Максим on 5/22/18.
//

#pragma once

#include "SDL_mixer.h"
#include <iostream>
#include <string>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    Mix_Chunk* LoadSFX(std::string title);
    Mix_Music* LoadTrack(std::string title);

    void PlayTrack(Mix_Music* t, int loop);
    void PlaySFX(Mix_Chunk* t);

private:
    Mix_Music* track;
    Mix_Chunk* sfx;
};