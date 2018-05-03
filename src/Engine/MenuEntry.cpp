//
//  MenuEntry.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/11/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "MenuEntry.hpp"

MenuEntry::MenuEntry(SDL_Renderer* r) : menuEntryTexture(r)
{
    renderer = r;
}

MenuEntry::~MenuEntry()
{
    Free();
}

bool MenuEntry::Create(SDL_Color color, std::string text, std::string font, int fontSize)
{
    menuEntryFont = TTF_OpenFont(font.c_str(), fontSize);
    
    if (menuEntryFont == nullptr)
    {
        std::cout << "Failed to load title font: " << TTF_GetError() << std::endl;
        return false;
    }
    else
    {
        menuEntryColor = color;
        
        if (!menuEntryTexture.LoadFromRenderedText(text, menuEntryColor, menuEntryFont))
        {
            std::cout << "Failed to render text texture!" << std::endl;
            return false;
        }
    }
    
    return true;
}

void MenuEntry::Render(int menuEntryX, int menuEntryY)
{
    Uint8 alpha = 255;
    
    x = menuEntryX;
    y = menuEntryY;
    
    if (Active)
    {
        menuEntryTexture.SetAlpha(alpha);
    }
    else
    {
        menuEntryTexture.SetAlpha(alpha - (Uint8)200);
    }
    
    menuEntryTexture.Render(x, y);
}

void MenuEntry::Free()
{
    menuEntryTexture.Free();
}
