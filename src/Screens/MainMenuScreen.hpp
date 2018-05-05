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
#include <SDL2/SDL.h>
#include "Screen.hpp"
#include "../Engine/MenuEntry.hpp"

class MainMenuScreen : public virtual Screen
{
public:
    MainMenuScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~MainMenuScreen() override;

    void LoadContent() override;
    void Update(SDL_Event* event) override;
    void Render() override;

    bool QuitFromMainMenu = false;
    bool StartNewGame = false;
    bool ShowHowTo = false;

private:
    SDL_Renderer * renderer;
    SDL_Event* event;

    SDL_Color textColor = { 0, 0, 0 };

    MenuEntry* startGame;
    MenuEntry* howTo;
    MenuEntry* quit;

    std::vector<MenuEntry*> menuEntries;
    std::vector<MenuEntry*>::iterator it;

    int width;
    int height;
};
