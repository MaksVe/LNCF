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
    Mix_FreeChunk(sfx);
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

Mix_Chunk* SoundManager::LoadSFX(std::string title)
{
    sfx = Mix_LoadWAV(title.c_str());
    if (sfx == nullptr)
    {
        std::cout << "Failed to load sfx: " << Mix_GetError() << std::endl;
    }

    return sfx;
}

void SoundManager::PlayTrack(Mix_Music* t, int loop)
{
    Mix_PlayMusic(t, loop);
}

void SoundManager::PlaySFX(Mix_Chunk* t)
{
    Mix_PlayChannel(-1, t, 0);
}