//
// Created by Максим on 5/22/18.
//

#include "SoundManager.hpp"

SoundManager::SoundManager()
{
    track   = nullptr;
    sfx     = nullptr;
}

SoundManager::~SoundManager()
{
    Mix_FreeMusic(track);
    Mix_FreeMusic(sfx);
    track = nullptr;
    sfx = nullptr;
}

Mix_Music* SoundManager::LoadTrack(std::string title)
{
    track = Mix_LoadMUS(title.c_str());
    if (track == nullptr)
    {
        std::cout << "Failed to load: " << title << " " << Mix_GetError() << std::endl;
    }

    return track;
}

bool SoundManager::LoadSFX(std::string title)
{
    sfx = Mix_LoadMUS(title.c_str());
    if (sfx == nullptr)
    {
        std::cout << "Failed to load sfx: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void SoundManager::PlayTrack(Mix_Music* t, int loop)
{
    Mix_PlayMusic(t, loop);
}

void SoundManager::PlaySFX(Mix_Music* t)
{
    Mix_PlayMusic(t, 0);
}