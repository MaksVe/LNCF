//
//  MainMenuScreen.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "MainMenuScreen.hpp"

MainMenuScreen::MainMenuScreen(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer    = r;
    width       = screenWidth;
    height      = screenHeight;
    
    startGame   = new MenuEntry(renderer);
    howTo       = new MenuEntry(renderer);
    quit        = new MenuEntry(renderer);
    
    LoadContent();
    
    menuEntries.push_back(startGame);
    menuEntries.push_back(howTo);
    menuEntries.push_back(quit);
    
    it = begin(menuEntries);
}


MainMenuScreen::~MainMenuScreen()
{
    delete startGame;
    delete quit;
    delete howTo;
}

void MainMenuScreen::LoadContent()
{
    // start
    if (!startGame->Create(textColor, "Start", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }
    // howTo
    if (!howTo->Create(textColor, "HowTo", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }
    // quit
    if (!quit->Create(textColor, "Quit", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }
}

void MainMenuScreen::Update(SDL_Event* e)
{
    event = e;
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
            case SDLK_UP:
                if (it != menuEntries.begin())
                {
                    it--;
                }
                event->type = SDL_KEYUP;
                break;
            case SDLK_DOWN:
                if (it != menuEntries.end() - 1)
                {
                    it++;
                }
                event->type = SDL_KEYUP;
                break;
            case SDLK_RETURN:
                if (*it == quit)
                {
                    QuitFromMainMenu = true;
                    event->type = SDL_KEYUP;
                }
                else if (*it == startGame)
                {
                    StartNewGame = true;
                    event->type = SDL_KEYUP;
                }
                else if (*it == howTo)
                {
                    ShowHowTo = true;
                    event->type = SDL_KEYUP;
                }
            default:
                break;
        }
    }
}

void MainMenuScreen::Render()
{
    if (startGame != nullptr)
    {
        if ((*it) == startGame)
        {
            startGame->Active = true;
        }
        else
        {
            startGame->Active = false;
        }
        startGame->Render((width / 2) - (startGame->menuEntryTexture.GetWidth() / 2), (height / 2) - 20);
    }
    
    if (howTo != nullptr)
    {
        if ((*it) == howTo)
        {
            howTo->Active = true;
        }
        else
        {
            howTo->Active = false;
        }
        howTo->Render((width / 2) - (howTo->menuEntryTexture.GetWidth() / 2), (height / 2));
    }

    if (quit != nullptr)
    {
        if ((*it) == quit)
        {
            quit->Active = true;
        }
        else
        {
            quit->Active = false;
        }
        quit->Render((width / 2) - (quit->menuEntryTexture.GetWidth() / 2), (height / 2) + 20);
    }
}
