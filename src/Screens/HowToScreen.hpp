//
//  HowToScreen.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/11/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef HowToScreen_hpp
#define HowToScreen_hpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Screen.hpp"
#include "../Engine/MenuEntry.hpp"
#include "../Engine/Texture2D.hpp"

class HowToScreen : public virtual Screen
{
public:
    HowToScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~HowToScreen() override;
    
    void LoadContent() override;
    void Update(SDL_Event* event) override;
    void Render() override;
    
    bool BackToMainMenu = false;
    
private:
    SDL_Renderer * renderer;
    SDL_Event* event;
    
    MenuEntry* backToMainMenu;
    Texture2D* howToTexture;
    
    SDL_Color textColor = { 0, 0, 0 };
    
    std::vector<Texture2D*> menuEntries;
    std::vector<Texture2D*>::iterator it;
    
    int width;
    int height;
};
#endif /* HowToScreen_hpp */
