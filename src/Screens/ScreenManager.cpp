//
//  ScreenManager.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "ScreenManager.hpp"

ScreenManager::ScreenManager(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    this->mainMenu = new MainMenuScreen(renderer, screenWidth, screenHeight);
    this->level_1 = new Level_1(renderer, screenWidth, screenHeight);
    this->howToScreen = new HowToScreen(renderer, screenWidth, screenHeight);

    screens.push(mainMenu);
}


ScreenManager::~ScreenManager()
{
    delete mainMenu;
    delete level_1;
    delete howToScreen;
}

void ScreenManager::Update(SDL_Event *event, const Uint8* currentKeyStates)
{
    screens.top()->Update(event, currentKeyStates);
    
    if (mainMenu->QuitFromMainMenu)
    {
        QuitGameFromMenu = true;
    }
    else if (mainMenu->StartNewGame)
    {
        screens.push(level_1);
        mainMenu->StartNewGame = false;
    }
    else if (mainMenu->ShowHowTo)
    {
        screens.push(howToScreen);
        mainMenu->ShowHowTo = false;
    }
    
    if (howToScreen->BackToMainMenu)
    {
        screens.pop();
        howToScreen->BackToMainMenu = false;
    }

    if (level_1->PlayerWon)
    {
        screens.pop();
        level_1->PlayerWon = false;
    }
}

void ScreenManager::Render()
{
    screens.top()->Render();
}
