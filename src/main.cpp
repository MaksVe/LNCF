#include <iostream>
#include "SDL.h"
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
