#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>

class App {
    public:
        App();
        int onExecute();

    private:
        bool onInit();
        void onEvent(SDL_Event* event);
        void onLoop();
        void onRender();
        void onCleanup();

    private:
        bool running;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif