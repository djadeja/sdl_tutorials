#include "Area.h"

Area Area::areacontrol;

Area::Area() {
    textureTileset = NULL;
}

bool Area::onLoad(SDL_Renderer *rendererDisplay, string file) {
    mapList.clear();

    FILE *fileHandle = fopen(file.c_str(), "r");

    if (fileHandle == NULL) {
        return false;
    }

    char tilesetFile[255];

    fscanf(fileHandle, "%s\n", tilesetFile);
    textureTileset = new Texture(rendererDisplay, tilesetFile);

    fscanf(fileHandle, "%d", &areaSize);

    for (int x = 0; x < areaSize; ++x) {
        for (int y = 0; y < areaSize; ++y) {
            char mapFile[255];
            fscanf(fileHandle, "%s ", mapFile);

            Map map;
            if (map.onLoad(mapFile) == false) {
                fclose(fileHandle);
                return false;
            }

            map.textureTileset = textureTileset;
            mapList.push_back(map);
        }
        fscanf(fileHandle, "\n");
    }
    fclose(fileHandle);
    return true;
}

void Area::onRender(SDL_Renderer *rendererDisplay, int cameraX, int cameraY) {

    int mapWidth = MAP_WIDTH * TILE_WIDTH;
    int mapHeight = MAP_HEIGHT * TILE_HEIGHT;

    int firstID = -cameraX / mapWidth;
    firstID += ((-cameraY /mapHeight) * areaSize);

    for (int i = 0; i < 4; ++i) {
        int id = firstID + ((i / 2) * areaSize) + (i % 2);

        if (id < 0 || id >= mapList.size())
            continue;
        
        int x = (id % areaSize) * mapWidth + cameraX;
        int y = (id / areaSize) * mapHeight + cameraY;

        mapList[id].onRender(rendererDisplay, x, y);
    }
}

void Area::onCleanup() {
    if (textureTileset)
        delete textureTileset;
    textureTileset = NULL;
    mapList.clear();
}

Map* Area::getMap(int X, int Y) {
    int mapWidth  = MAP_WIDTH * TILE_WIDTH;
    int mapHeight = MAP_HEIGHT * TILE_HEIGHT;
 
    int ID = X / mapWidth;
        ID = ID + ((Y / mapHeight) * areaSize);
 
    if(ID < 0 || ID >= mapList.size()) {
        return NULL;
    }
 
    return &mapList[ID];
}
 
Tile* Area::getTile(int X, int Y) {
    int mapWidth  = MAP_WIDTH * TILE_WIDTH;
    int mapHeight = MAP_HEIGHT * TILE_WIDTH;
 
    Map* map = getMap(X, Y);
 
    if(map == NULL)
        return NULL;
 
    X = X % mapWidth;
    Y = Y % mapHeight;
 
    return map->getTile(X, Y);
}
