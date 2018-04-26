#include <iostream>
#include "SDL2/SDL.h"
#include "Game/Game.hpp"

int main(int argc, char *argv[])
{
    Game* game = new Game();

    if (game->Init())
    {
        game->Run();
    }

    delete game;
    game = nullptr;

    return 0;
}