#include "Texture.h"

Texture::Texture(SDL_Renderer* sdlRenderer, const string& bmpfile) : sdlTexture(NULL) {
    if (sdlRenderer != NULL) {
        SDL_Surface *bmpSurface = SDL_LoadBMP(bmpfile.c_str());
        if (bmpSurface) {
            this->sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, bmpSurface);
        }
    }
}

Texture::Texture(SDL_Renderer* sdlRenderer, const string& bmpfile, int R, int G, int B) : sdlTexture(NULL) {
    if (sdlRenderer != NULL) {
        SDL_Surface *bmpSurface = SDL_LoadBMP(bmpfile.c_str());

        if (bmpSurface) {
            SDL_SetColorKey(bmpSurface, SDL_TRUE | SDL_RLEACCEL, SDL_MapRGB(bmpSurface->format, R, G, B));
            this->sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, bmpSurface);
        }
    }
}

Texture::~Texture() {
    if (sdlTexture)
        SDL_DestroyTexture(sdlTexture);
}

int Texture::copyTo(SDL_Renderer* sdlRenderer) {
    if (sdlTexture && sdlRenderer) {
        return SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
    }
    return 0;
}

int Texture::copyTo(SDL_Renderer* sdlRenderer, int x, int y) {
    if (sdlTexture && sdlRenderer) {        
        int srcTextW;
        int srcTextH;
        SDL_QueryTexture(sdlTexture, NULL, NULL, &srcTextW, &srcTextH);
        SDL_Rect destR;
        destR.x = x;
        destR.y = y;
        destR.w = srcTextW;
        destR.h = srcTextH;
        return SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &destR);
    }
    return 0;
}

int Texture::copyTo(SDL_Renderer* sdlRenderer, int dX, int dY, int sX, int sY, int sW, int sH) {
     if (sdlTexture && sdlRenderer) {        
        
        SDL_Rect srcR, destR;
        srcR.x = sX;
        srcR.y = sY;
        srcR.w = sW;
        srcR.h = sH;
        destR.x = dX;
        destR.y = dY;
        destR.w = sW;
        destR.h = sH;
        return SDL_RenderCopy(sdlRenderer, sdlTexture, &srcR, &destR);
    }
    return 0;
}