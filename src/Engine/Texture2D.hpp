//
//  Texture2D.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


/*This class was originally from Lazy Foo' Productions
 (http://lazyfoo.net/)*/

class Texture2D
{
public:
    Texture2D(SDL_Renderer * renderer);
    ~Texture2D();
    
    bool LoadFromFile(std::string path);
    bool LoadFromRenderedText(std::string textTexture, SDL_Color textColor, TTF_Font* font);
    
    void Free();
    
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetBlendMode(SDL_BlendMode blending);
    void SetAlpha(Uint8 alpha);
    
    void Render(int x, int y, SDL_Rect* rect = nullptr, double angle = 0.0,
                SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    int GetWidth();
    int GetHeight();
    
private:
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    TTF_Font* font;
    
    int width;
    int height;
};

#endif /* Texture2D_hpp */
