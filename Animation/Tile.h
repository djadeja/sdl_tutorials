#ifndef _TILE_H_
#define _TILE_H_

#include "Define.h"

enum class TileType {
    NONE = 0,
    NORMAL,
    BLOCK
};

class Tile {
    public:
        int tileID;
        TileType type;

    public:
        Tile();
};

#endif