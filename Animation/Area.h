#ifndef _AREA_H_
#define _AREA_H_

#include "SDL2/SDL.h"
#include "Map.h"
#include <vector>

using namespace std;

class Area {

    public:
        static Area     areacontrol;
        vector<Map>     mapList;

    private:
        int             areaSize;
        Texture         *textureTileset;

    public:
        Area();
        bool onLoad(SDL_Renderer *rendererDisplay, string file);
        void onRender(SDL_Renderer *rendererDisplay, int cameraX, int cameraY);
        void onCleanup();        
        Map* getMap(int x, int y); 
        Tile* getTile(int x, int y);
};

#endif