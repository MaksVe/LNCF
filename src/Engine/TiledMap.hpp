/* this class was originally from Code of Connor
 * (https://github.com/connorkuehl/sdl2-tiled-example)
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

typedef int gid;

struct tile
{
    SDL_Texture* sheet;
    int x;
    int y;
    int spriteX;
    int spriteY;
    int width;
    int height;

    tile (SDL_Texture* tileSet, int x = 0, int y = 0, int spriteX = 0, int spriteY = 0, int w = 0, int h = 0);
    void draw(SDL_Renderer* renderer);
};

class TiledMap
{
public:
    TiledMap(const std::string& name);
    void LoadContent(const std::string& path, SDL_Renderer* renderer);
    void LoadForeground(const std::string& path, SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    void RenderForeground(SDL_Renderer* renderer);

    SDL_Rect GetUpperEnd();
    SDL_Rect GetLeftEnd();
    SDL_Rect GetDownerEnd();
    SDL_Rect GetRightEnd();

    float MapWidth;

private:
    std::string name;
    int rows;
    int cols;
    int tileWidth;
    int tileHeight;
    std::vector<tile> tiles;
    std::map<gid, SDL_Texture*> tilesets;

    std::vector<tile> foregroundTiles;

    // Objects
    SDL_Rect nonWalkableDown;
    SDL_Rect nonWalkableUp;
    SDL_Rect nonWalkableLeft;
    SDL_Rect nonWalkableRight;
};
