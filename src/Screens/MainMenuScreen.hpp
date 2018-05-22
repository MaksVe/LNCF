//
//  MainMenuScreen.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Screen.hpp"
#include "../Engine/MenuEntry.hpp"
#include "../Engine/SoundManager.hpp"

class MainMenuScreen : public virtual Screen
{
public:
    MainMenuScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~MainMenuScreen() override;

    void LoadContent() override;
    void Update(SDL_Event* event, const Uint8* currentKeyStates) override;
    void Render() override;

    bool QuitFromMainMenu = false;
    bool StartNewGame = false;
    bool ShowHowTo = false;

private:
    SDL_Renderer * renderer;
    SDL_Event* event;

    SDL_Color textColor = { 255, 255, 255 };

    MenuEntry* startGame;
    MenuEntry* howTo;
    MenuEntry* quit;

    SoundManager* soundManager;
    Mix_Music* mainMenuTrack;

    std::vector<MenuEntry*> menuEntries;
    std::vector<MenuEntry*>::iterator it;

    int width;
    int height;
};
