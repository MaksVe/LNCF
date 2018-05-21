#include "TiledMap.hpp"
#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"
#include <iostream>
#include <algorithm>

tile::tile(SDL_Texture *tileSet, int x, int y, int spriteX, int spriteY, int w, int h) :
    sheet(tileSet), x(x), y(y), spriteX(spriteX), spriteY(spriteY), width(w), height(h)
{

}

void tile::draw(SDL_Renderer *renderer, SDL_Rect* camera)
{
    if (!renderer || !sheet)
    {
        return;
    }

    SDL_Rect src;
    src.x = spriteX;
    src.y = spriteY;
    src.w = width;
    src.h = height;

    SDL_Rect dest;
    dest.x = x - camera->x;
    dest.y = y;
    dest.w = src.w;
    dest.h = src.h;

    SDL_RenderCopy(renderer, sheet, &src, &dest);
}

TiledMap::TiledMap(const std::string &name) :
    name(name), rows(0), cols(0)
{

}

void TiledMap::LoadContent(const std::string& path, SDL_Renderer* renderer)
{
    // load and parse the tiled map
    tmx::Map tiledMap;
    tiledMap.load(path);

    // get map width
    MapWidth = tiledMap.getBounds().width;

    // the size of the map in tiles
    auto mapDimensions = tiledMap.getTileCount();
    rows = mapDimensions.y;
    cols = mapDimensions.x;

    // the dimensions of the tiles
    auto tileSize = tiledMap.getTileSize();
    tileWidth = tileSize.x;
    tileHeight = tileSize.y;

    // load all of the tiles and store them in a data structure
    auto& mapTilesets = tiledMap.getTilesets();
    for (auto& tset : mapTilesets)
    {
        auto surf = IMG_Load(tset.getImagePath().c_str());
        if (!surf)
        {
            std::cout << "Error loading tilemap: " << IMG_GetError() << std::endl;
        }
        auto tex = SDL_CreateTextureFromSurface(renderer, surf);
        tilesets.insert(std::pair<gid, SDL_Texture*>(tset.getFirstGID(), tex));
    }

    // get the required info from the tile and store it in the tiles data structure
    auto& mapLayers = tiledMap.getLayers();
    for (auto& layer : mapLayers)
    {
        // skip if it's not a tile layer
        if (layer->getType() != tmx::Layer::Type::Tile)
        {
            if (layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
                std::cout << "Found " << objects.size() << " objects in layer" << std::endl;
                for (auto& obj : objects)
                {
                    const std::string &objGroup = obj.getName();

                    if (objGroup == "nonWalkableDown")
                    {
                        nonWalkableDown.x = (int)obj.getPosition().x;
                        nonWalkableDown.y = (int)obj.getPosition().y + 3;
                        nonWalkableDown.w = (int)obj.getAABB().width;
                        nonWalkableDown.h = (int)obj.getAABB().height;
                    }
                    else if (objGroup == "nonWalkableUp")
                    {
                        nonWalkableUp.x = (int)obj.getPosition().x;
                        nonWalkableUp.y = (int)obj.getPosition().y - 27;
                        nonWalkableUp.w = (int)obj.getAABB().width;
                        nonWalkableUp.h = (int)obj.getAABB().height;
                    }
                    else if (objGroup == "leftEnd")
                    {
                        nonWalkableLeft.x = (int)obj.getPosition().x;
                        nonWalkableLeft.y = (int)obj.getPosition().y;
                        nonWalkableLeft.w = (int)obj.getAABB().width;
                        nonWalkableLeft.h = (int)obj.getAABB().height;
                    }
                    else if (objGroup == "rightEnd")
                    {
                        nonWalkableRight.x = (int)obj.getPosition().x;
                        nonWalkableRight.y = (int)obj.getPosition().y;
                        nonWalkableRight.w = (int)obj.getAABB().width;
                        nonWalkableRight.h = (int)obj.getAABB().height;
                    }
                    else if (objGroup == "endPoint")
                    {
                        endPoint.x = (int)obj.getPosition().x;
                        endPoint.y = (int)obj.getPosition().y;
                        endPoint.w = (int)obj.getAABB().width;
                        endPoint.h = (int)obj.getAABB().height;
                    }
                }
            }

            continue;
        }
        if (layer->getName() == "foregroundObjects")
        {
            continue;
        }

        auto* tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());
        // get tiles from this layer
        auto& layerTiles = tileLayer->getTiles();

        for (auto y = 0; y < rows; ++y)
        {
            for (auto x = 0; x < cols; ++x)
            {
                // convert x, y coordinates into an index that we can access at
                auto tileIndex = x + (y * cols);
                auto currentGid = layerTiles[tileIndex].ID;
                // skip an empty tile
                if (currentGid == 0)
                {
                    continue;
                }

                // find the tileset that this tile belongs to
                auto tsetGid = -1;
                for (auto& ts: tilesets)
                {
                    if (ts.first <= currentGid)
                    {
                        tsetGid = ts.first;
                        break;
                    }
                }

                // if valid tileset not found, skip the tile
                if (tsetGid == -1)
                {
                    continue;
                }

                // normalize the GID
                currentGid -= tsetGid;
                // find the dimensions of the tile sheet
                auto tsWidth = 0;
                auto tsHeight = 0;
                SDL_QueryTexture(tilesets[tsetGid], nullptr, nullptr, &tsWidth, &tsHeight);

                // calculate the area on the tilesheet to draw from
                auto regionX = (currentGid % (tsWidth / tileWidth)) * tileWidth;
                auto regionY = (currentGid / (tsWidth / tileHeight)) * tileHeight;

                // calculate the world position of our tile
                auto xPos = x * tileWidth;
                auto yPos = y * tileHeight;

                tile t(tilesets[tsetGid], xPos, yPos, regionX, regionY, tileWidth, tileHeight);
                tiles.push_back(t);

            }
        }
    }
}

void TiledMap::LoadForeground(const std::string &path, SDL_Renderer *renderer)
{
    // load and parse the tiled map
    tmx::Map tiledMap;
    tiledMap.load(path);

    // get map width
    MapWidth = tiledMap.getBounds().width;

    // the size of the map in tiles
    auto mapDimensions = tiledMap.getTileCount();
    rows = mapDimensions.y;
    cols = mapDimensions.x;

    // the dimensions of the tiles
    auto tileSize = tiledMap.getTileSize();
    tileWidth = tileSize.x;
    tileHeight = tileSize.y;

    // load all of the tiles and store them in a data structure
    auto& mapTilesets = tiledMap.getTilesets();
    for (auto& tset : mapTilesets)
    {
        auto surf = IMG_Load(tset.getImagePath().c_str());
        if (!surf)
        {
            std::cout << "Error loading tilemap: " << IMG_GetError() << std::endl;
        }
        auto tex = SDL_CreateTextureFromSurface(renderer, surf);
        tilesets.insert(std::pair<gid, SDL_Texture*>(tset.getFirstGID(), tex));
    }

    // get the required info from the tile and store it in the tiles data structure
    auto& mapLayers = tiledMap.getLayers();
    for (auto& layer : mapLayers)
    {
        // skip if it's not a tile layer
        if (layer->getType() != tmx::Layer::Type::Tile)
        {
            continue;
        }
        if (layer->getName() == "foregroundObjects")
        {
            auto* tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());
            // get tiles from this layer
            auto& layerTiles = tileLayer->getTiles();

            for (auto y = 0; y < rows; ++y)
            {
                for (auto x = 0; x < cols; ++x)
                {
                    // convert x, y coordinates into an index that we can access at
                    auto tileIndex = x + (y * cols);
                    auto currentGid = layerTiles[tileIndex].ID;
                    // skip an empty tile
                    if (currentGid == 0)
                    {
                        continue;
                    }

                    // find the tileset that this tile belongs to
                    auto tsetGid = -1;
                    for (auto& ts: tilesets)
                    {
                        if (ts.first <= currentGid)
                        {
                            tsetGid = ts.first;
                            break;
                        }
                    }

                    // if valid tileset not found, skip the tile
                    if (tsetGid == -1)
                    {
                        continue;
                    }

                    // normalize the GID
                    currentGid -= tsetGid;
                    // find the dimensions of the tile sheet
                    auto tsWidth = 0;
                    auto tsHeight = 0;
                    SDL_QueryTexture(tilesets[tsetGid], nullptr, nullptr, &tsWidth, &tsHeight);

                    // calculate the area on the tilesheet to draw from
                    auto regionX = (currentGid % (tsWidth / tileWidth)) * tileWidth;
                    auto regionY = (currentGid / (tsWidth / tileHeight)) * tileHeight;

                    // calculate the world position of our tile
                    auto xPos = x * tileWidth;
                    auto yPos = y * tileHeight;

                    tile t(tilesets[tsetGid], xPos, yPos, regionX, regionY, tileWidth, tileHeight);
                    foregroundTiles.push_back(t);
                }
            }
        }
    }
}

void TiledMap::Render(SDL_Renderer *renderer, SDL_Rect* camera)
{
    for (auto& tile : tiles)
    {
        tile.draw(renderer, camera);
    }
}

void TiledMap::RenderForeground(SDL_Renderer *renderer, SDL_Rect* camera)
{
    for (auto& tile : foregroundTiles)
    {
        tile.draw(renderer, camera);
    }
}

SDL_Rect TiledMap::GetUpperEnd()
{
    return nonWalkableUp;
}

SDL_Rect TiledMap::GetRightEnd()
{
    return nonWalkableRight;
}

SDL_Rect TiledMap::GetDownerEnd()
{
    return nonWalkableDown;
}

SDL_Rect TiledMap::GetLeftEnd()
{
    return nonWalkableLeft;
}

SDL_Rect TiledMap::GetEndPoint()
{
    return endPoint;
}
