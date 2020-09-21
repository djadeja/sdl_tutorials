#ifndef _MAP_H_
#define _MAP_H_

#include "SDL2/SDL.h"
#include <vector>
#include <string>

#include "Tile.h"
#include "Texture.h"

using namespace std;

class Map {
    public:
        Texture *textureTileset;

    private:
        vector<Tile> tileList;

    public:
        Map();
        bool onLoad(string file);
        void onRender(SDL_Renderer *rendererDisplay, int mapX, int mapY);
        Tile* getTile(int x, int y);
};

#endif