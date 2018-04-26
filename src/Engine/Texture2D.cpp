//
//  Texture2D.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Texture2D.hpp"

Texture2D::Texture2D(SDL_Renderer * r)
{
    renderer = r;
    texture = nullptr;
    font = nullptr;
    width = 0;
    height = 0;
}


Texture2D::~Texture2D()
{
    Free();
}

bool Texture2D::LoadFromFile(std::string path)
{
    Free();
    
    SDL_Texture* newTexture = nullptr;
    
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cout << "Unable to load image: " << path << " " << IMG_GetError() << std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (newTexture == nullptr)
        {
            std::cout << "Unable to create texture: " << path << " " << SDL_GetError() << std::endl;
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }
        
        SDL_FreeSurface(surface);
    }
    
    texture = newTexture;
    return texture != nullptr;
}

bool Texture2D::LoadFromRenderedText(std::string textTexture, SDL_Color textColor, TTF_Font* f)
{
    Free();
    
    font = f;
    
    SDL_Texture* newTexture = nullptr;
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, textTexture.c_str(), textColor);
    if (surface == nullptr)
    {
        std::cout << "Unable to render text surface: " << TTF_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (newTexture == nullptr)
        {
            std::cout << "Unable to create text texture: " << SDL_GetError() << std::endl;
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }
        
        SDL_FreeSurface(surface);
    }
    
    texture = newTexture;
    return texture != nullptr;
}

void Texture2D::Free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture2D::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture2D::SetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(texture, blending);
}

void Texture2D::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture2D::Render(int x, int y, SDL_Rect* rect, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = { x, y, width, height };
    if (rect != nullptr)
    {
        renderQuad.w = rect->w;
        renderQuad.h = rect->h;
    }
    
    SDL_RenderCopyEx(renderer, texture, rect, &renderQuad, angle, center, flip);
}

int Texture2D::GetWidth()
{
    return width;
}

int Texture2D::GetHeight()
{
    return height;
}
