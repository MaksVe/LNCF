//
//  Game.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../Screens/ScreenManager.hpp"

/*Some parts of this class was originally from Lazy Foo' Productions
 (http://lazyfoo.net/)*/

class Game
{
public:
    Game();
    ~Game();
    
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 400;
    
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

#endif /* Game_hpp */
