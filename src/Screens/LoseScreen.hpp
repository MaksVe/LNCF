//
// Created by Максим on 5/22/18.
//

#pragma once

#include <iostream>
#include <vector>

#include "Screen.hpp"
#include "../Engine/MenuEntry.hpp"
#include "../Engine/Texture2D.hpp"

class LoseScreen : public virtual Screen
{
public:
    LoseScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~LoseScreen() override;
    void LoadContent() override;
    void Update(SDL_Event* event, const Uint8* currentKeyStates) override;
    void Render() override;

    bool BackToMainMenu = false;
    bool TryAgain = false;

private:
    SDL_Renderer * renderer;
    SDL_Event* event;

    TTF_Font* loseTextFont;
    Texture2D* LoseTextTexture;
    MenuEntry* backToMainMenu;
    MenuEntry* tryAgain;

    SDL_Color textColor = { 255, 255, 255 };

    std::vector<MenuEntry*> menuEntries;
    std::vector<MenuEntry*>::iterator it;

    int width;
    int height;
};
