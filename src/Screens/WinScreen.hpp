//
// Created by Максим on 5/23/18.
//

#pragma once

#include <iostream>
#include <vector>

#include "Screen.hpp"
#include "../Engine/MenuEntry.hpp"
#include "../Engine/Texture2D.hpp"

class WinScreen : public virtual Screen
{
public:
    WinScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~WinScreen() override;
    void LoadContent() override;
    void Update(SDL_Event* event, const Uint8* currentKeyStates) override;
    void Render() override;

    bool BackToMainMenu = false;
    bool RestartLevel = false;

private:
    SDL_Renderer * renderer;
    SDL_Event* event;

    TTF_Font* winTextFont;
    Texture2D* winTextTexture;
    MenuEntry* backToMainMenu;
    MenuEntry* restartLevel;

    SDL_Color textColor = { 255, 255, 255 };

    std::vector<MenuEntry*> menuEntries;
    std::vector<MenuEntry*>::iterator it;

    int width;
    int height;
};
