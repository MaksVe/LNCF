//
//  ScreenManager.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include <stack>
#include <SDL2/SDL.h>
#include "MainMenuScreen.hpp"
#include "Level_1.hpp"
#include "HowToScreen.hpp"

class ScreenManager
{
public:
    ScreenManager(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~ScreenManager();
    
    void Update(SDL_Event* event);
    void Render();
    
    bool QuitGameFromMenu;
    
private:
    MainMenuScreen * mainMenu;
    Level_1* level_1;
    HowToScreen* howToScreen;
    
    //Screen* currentScreen;
    
    std::stack<Screen*> screens;
};

#endif /* ScreenManager_hpp */
