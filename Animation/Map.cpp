#include "Map.h"

Map::Map() {
  
    textureTileset = NULL;
}

bool Map::onLoad(string file) {
    tileList.clear();

    FILE *fileHandle = fopen(file.c_str(), "r");
    if (!fileHandle) {
        return false;
    }

    for (int y=0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            
            Tile tile;
            fscanf(fileHandle, "%d:%d ", &tile.tileID, &tile.type);

            tileList.push_back(tile);
        }
        fscanf(fileHandle, "\n");        
    }
    fclose(fileHandle);
    return true;
}

void Map::onRender(SDL_Renderer *rendererDisplay, int mapX, int mapY) {

    if (textureTileset == NULL)
        return;
    
    int tilesetWidth = textureTileset->getWidth() / TILE_WIDTH;
    int tilesetHeight = textureTileset->getHeight() / TILE_HEIGHT;

    int id = 0;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            ++id;
            if (tileList[id].type == TileType::NONE) {
                continue;
            }
            int tX = mapX + (x * TILE_WIDTH);
            int tY = mapY + (y * TILE_HEIGHT);

            int tilesetX = (tileList[id].tileID % tilesetWidth) * TILE_WIDTH;
            int tilesetY = (tileList[id].tileID / tilesetWidth) * TILE_HEIGHT;

            textureTileset->copyTo(rendererDisplay, tX, tY, tilesetX, tilesetY, TILE_WIDTH, TILE_HEIGHT);
        }
    }
}

Tile* Map::getTile(int X, int Y) {
    int ID = 0;
 
    ID = X / TILE_WIDTH;
    ID = ID + (MAP_WIDTH * (Y / TILE_HEIGHT));
 
    if(ID < 0 || ID >= tileList.size()) {
        return NULL;
    }
 
    return &tileList[ID];
}
