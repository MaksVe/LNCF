//
//  MenuEntry.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/11/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include "Texture2D.hpp"

class MenuEntry
{
public:
    MenuEntry(SDL_Renderer* r);
    ~MenuEntry();

    bool Create(SDL_Color color, std::string text, std::string font, int fontSize);
    void Render(int menuEntryX, int menuEntryY);
    void Free();

    bool Active = false;

    Texture2D menuEntryTexture;

private:
    SDL_Renderer* renderer;
    TTF_Font* menuEntryFont;

    SDL_Color menuEntryColor;

    int x;
    int y;
};
