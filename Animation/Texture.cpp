#include "Texture.h"
#include "SDL2_image/SDL_image.h"

// Texture::Texture(SDL_Renderer* sdlRenderer, const string& bmpfile) : sdlTexture(NULL) {
//     if (sdlRenderer != NULL) {
//         SDL_Surface *bmpSurface = SDL_LoadBMP(bmpfile.c_str());
//         if (bmpSurface) {
//             this->sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, bmpSurface);
//         }
//     }
// }

Texture::Texture(SDL_Renderer* sdlRenderer, const string& file) : sdlTexture(NULL), width(0), height(0) {
    if (sdlRenderer != NULL) {
        sdlTexture = IMG_LoadTexture(sdlRenderer, file.c_str());       
        SDL_QueryTexture(sdlTexture, NULL, NULL, &width, &height);
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
        SDL_Rect destR;
        destR.x = x;
        destR.y = y;
        destR.w = getWidth();
        destR.h = getHeight();
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

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}