//
//  HowToScreen.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/11/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "HowToScreen.hpp"

HowToScreen::HowToScreen(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer = r;
    width = screenWidth;
    height = screenHeight;
    
    backToMainMenu = new MenuEntry(renderer);
    howToTexture = new Texture2D(renderer);
    
    LoadContent();

    it = menuEntries.begin();
}

HowToScreen::~HowToScreen()
{
    delete backToMainMenu;
    delete howToTexture;
}

void HowToScreen::LoadContent()
{
    if (!backToMainMenu->Create(textColor, "Back", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }
}

void HowToScreen::Update(SDL_Event* e, const Uint8* currentKeyStates)
{
    event = e;
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.sym == SDLK_RETURN || event->key.keysym.sym == SDLK_ESCAPE)
        {
            BackToMainMenu = true;
            event->type = SDL_KEYUP;
        }
    }
}

void HowToScreen::Render()
{  
    if (backToMainMenu != nullptr)
    {
        backToMainMenu->Active = true;
        backToMainMenu->Render((width / 2) - (backToMainMenu->menuEntryTexture.GetWidth() / 2), 200);
    }
}

