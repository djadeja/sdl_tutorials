#ifndef _CPLAYER_H_
#define _CPLAYER_H_
 
#include "Entity.h"
 
class Player : public Entity {
    public:
        Player();
 
        bool onLoad(SDL_Renderer* sdlRenderer, const string& file, int width, int height, int maxFrames);
 
        void onLoop();
 
        void onRender(SDL_Renderer* rendererDisplay);
 
        void onCleanup();
 
        void onAnimate();
 
        void onCollision(Entity* Entity);
};
 
#endif