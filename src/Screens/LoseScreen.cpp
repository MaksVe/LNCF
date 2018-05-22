//
// Created by Максим on 5/22/18.
//

#include "LoseScreen.hpp"

LoseScreen::LoseScreen(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer = r;
    width = screenWidth;
    height = screenHeight;

    backToMainMenu = new MenuEntry(renderer);
    tryAgain = new MenuEntry(renderer);

    LoadContent();

    menuEntries.push_back(backToMainMenu);
    menuEntries.push_back(tryAgain);

    it = menuEntries.begin();
}

LoseScreen::~LoseScreen()
{
    delete backToMainMenu;
    delete tryAgain;
}

void LoseScreen::LoadContent()
{
    loseTextFont = TTF_OpenFont("PressStart2P.ttf", 16);
    LoseTextTexture->LoadFromRenderedText("You Lose", textColor, loseTextFont);

    if (!backToMainMenu->Create(textColor, "Return to Main Menu", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }

    if (!tryAgain->Create(textColor, "Try Again", "PressStart2P.ttf", 16))
    {
        std::cout << "Unable to create menu entry!" << std::endl;
    }
}

void LoseScreen::Update(SDL_Event* e, const Uint8* currentKeyStates)
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
                else if (*it == tryAgain)
                {
                    // stop music
                    TryAgain = true;
                    event->type = SDL_KEYUP;
                }
            default:
                break;
        }
    }
}

void LoseScreen::Render()
{
    LoseTextTexture->Render((width / 2) - (LoseTextTexture->GetWidth() / 2), 50);

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

    if (tryAgain != nullptr)
    {
        if ((*it) == tryAgain)
        {
            tryAgain->Active = true;
        }
        else
        {
            tryAgain->Active = false;
        }
        tryAgain->Render((width / 2) - (tryAgain->menuEntryTexture.GetWidth() / 2), (height / 2));
    }
}