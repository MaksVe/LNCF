//
// Created by Максим on 5/23/18.
//

#include "WinScreen.hpp"

WinScreen::WinScreen(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer = r;
    width = screenWidth;
    height = screenHeight;

    backToMainMenu = new MenuEntry(renderer);
    restartLevel = new MenuEntry(renderer);
    winTextTexture = new Texture2D(renderer);

    LoadContent();

    menuEntries.push_back(backToMainMenu);
    menuEntries.push_back(restartLevel);

    it = menuEntries.begin();
}

WinScreen::~WinScreen()
{
    delete backToMainMenu;
    delete restartLevel;
    delete winTextTexture;
}

void WinScreen::LoadContent()
{
    winTextFont = TTF_OpenFont("PressStart2P.ttf", 16);
    winTextTexture->LoadFromRenderedText("You Win", textColor, winTextFont);

    if (!backToMainMenu->Create(textColor, "Return to Main Menu", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }

    if (!restartLevel->Create(textColor, "Restart Level", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }
}

void WinScreen::Update(SDL_Event* e, const Uint8* currentKeyStates)
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
                if (*it == backToMainMenu)
                {
                    BackToMainMenu = true;
                    event->type = SDL_KEYUP;
                }
                else if (*it == restartLevel)
                {
                    // stop music
                    RestartLevel = true;
                    event->type = SDL_KEYUP;
                }
            default:
                break;
        }
    }
}

void WinScreen::Render()
{
    winTextTexture->Render((width / 2) - (winTextTexture->GetWidth() / 2), 50);

    if (backToMainMenu != nullptr)
    {
        if ((*it) == backToMainMenu)
        {
            backToMainMenu->Active = true;
        }
        else
        {
            backToMainMenu->Active = false;
        }
        backToMainMenu->Render((width / 2) - (backToMainMenu->menuEntryTexture.GetWidth() / 2), (height / 2) - 20);
    }

    if (restartLevel != nullptr)
    {
        if ((*it) == restartLevel)
        {
            restartLevel->Active = true;
        }
        else
        {
            restartLevel->Active = false;
        }
        restartLevel->Render((width / 2) - (restartLevel->menuEntryTexture.GetWidth() / 2), (height / 2));
    }
}