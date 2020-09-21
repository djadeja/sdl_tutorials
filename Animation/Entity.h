#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include "Animation.h"
#include "Texture.h"
#include "Tile.h"

using namespace std;

enum {
    ENTITY_TYPE_GENERIC = 0, 
    ENTITY_TYPE_PLAYER
};
 
enum {
    ENTITY_FLAG_NONE     = 0, 
    ENTITY_FLAG_GRAVITY  = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY  = 0x00000004
};

class Entity {

    public:
        static vector<Entity *> entityList;

    protected:
        Animation   animControl;
        Texture     *textureEntity;

    public:
        float   x;
        float   y;
        int     width;
        int     height;
        bool        MoveLeft;
        bool        MoveRight;
 
    public:
        int        Type;
 
        bool        Dead;
        int        Flags;
 
    protected:
        float        SpeedX;
        float        SpeedY;
 
        float        AccelX;
        float        AccelY;
 
    public:
        float        MaxSpeedX;
        float        MaxSpeedY;
 
    protected:
        int             CurrentFrameCol;
        int             CurrentFrameRow;
 
    protected:
        int        Col_X;
        int        Col_Y;
        int        Col_Width;
        int        Col_Height;
 
    public:
        Entity(); 
        virtual ~Entity();
 
    public:
        virtual bool onLoad(SDL_Renderer* sdlRenderer, const string& file, int width, int height, int maxFrames);
        
        virtual void onLoop();
         
        virtual void onRender(SDL_Renderer* rendererDisplay);
 
        virtual void onCleanup();
 
        virtual void onAnimate();
 
        virtual void onCollision(Entity* Entity);
 
    public:
        void     OnMove(float MoveX, float MoveY);
 
        void     StopMove();
 
    public:
        bool     Collides(int oX, int oY, int oW, int oH);
 
    private:
        bool     PosValid(int NewX, int NewY);
 
        bool     PosValidTile(Tile* Tile);
 
        bool     PosValidEntity(Entity* Entity, int NewX, int NewY);        
};
 
class EntityCol {
    public:
        static std::vector<EntityCol>    EntityColList;
 
    public:
        Entity* EntityA;
        Entity* EntityB;
 
    public:
        EntityCol();
};
 
#endif
