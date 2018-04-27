//
//  Game.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Game.hpp"

Game::Game()
{
    window = nullptr;
    renderer = nullptr;
}


Game::~Game()
{
    delete screenManager;
}

bool Game::Init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Init error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cout << "Unable to create window: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            // Create renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr)
            {
                std::cout << "Unable to create renderer: " << SDL_GetError() << std::endl;
                return false;
            }
            else
            {
                // Initialize SDL_font
                if (TTF_Init() == -1)
                {
                    std::cout << "SDL_ttf init error: " << TTF_GetError() << std::endl;
                    return false;
                }
                else
                {
                    // Initialize PNG
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        std::cout << "SDL_image init error: " << IMG_GetError() << std::endl;
                        return false;
                    }
                    
                    return true;
                }
            }
        }
    }
}

void Game::Run()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int frameTime;
    Uint32 frameStart;

    bool quit = false;
    SDL_Event e;
    screenManager = new ScreenManager(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // main loop
    while (!quit)
    {
        frameStart = SDL_GetTicks();

        Update(&e);
        Render();

        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || screenManager->QuitGameFromMenu)
            {
                quit = true;
            }
        }
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    Close();
}



void Game::Close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::Update(SDL_Event* e)
{
    screenManager->Update(e);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD); // test
    SDL_RenderClear(renderer);
    
    screenManager->Render();
    
    SDL_RenderPresent(renderer);
}
