#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Texture {

    public:
        Texture(SDL_Renderer* sdlRenderer, const string& bmpfile);
        Texture(SDL_Renderer* sdlRenderer, const string& bmpfile, int R, int G, int B);
        ~Texture();
        int copyTo(SDL_Renderer* sdlRenderer);
        int copyTo(SDL_Renderer* sdlRenderer, int X, int Y);
        int copyTo(SDL_Renderer* sdlRenderer, int dX, int dY, int sX, int sY, int sW, int sH);
        
    private:
        SDL_Texture *sdlTexture;
};

#endif