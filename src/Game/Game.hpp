//
//  Game.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../Screens/ScreenManager.hpp"

/*Some parts of this class was originally from Lazy Foo' Productions
 (http://lazyfoo.net/)*/

class Game
{
public:
    Game();
    ~Game();

    const static int SCREEN_WIDTH = 427;
    const static int SCREEN_HEIGHT = 240;

    bool Init();
    void Run();

    void Update(SDL_Event* event);
    void Render();

    void Close();

private:
    SDL_Window * window;
    SDL_Renderer* renderer;
    SDL_Event* event;

    ScreenManager* screenManager;
};
