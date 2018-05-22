//
//  ScreenManager.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <stack>
#include "SDL.h"
#include "MainMenuScreen.hpp"
#include "Level_1.hpp"
#include "HowToScreen.hpp"
#include "LoseScreen.hpp"

class ScreenManager
{
public:
    ScreenManager(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~ScreenManager();

    void Update(SDL_Event* event, const Uint8* currentKeyStates);
    void Render();

    bool QuitGameFromMenu;

private:
    MainMenuScreen * mainMenu;
    Level_1* level_1;
    HowToScreen* howToScreen;
    LoseScreen* loseScreen;

    //Screen* currentScreen;

    std::stack<Screen*> screens;
};
