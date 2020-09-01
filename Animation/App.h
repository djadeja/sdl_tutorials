#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>
#include "Event.h"
#include "Animation.h"
#include <vector>

using namespace std;

class Texture;

enum class CellType {
            None,
            X,
            O
        };

enum class Player {
            A,
            B
        };

class App : public Event {
    public:
        App();
        int onExecute();

    private:
        bool onInit();
        void onEvent(SDL_Event* event);
        void onLoop();
        void onRender();
        void onCleanup();
        void OnExit();
        void reset();
        void setCell(int pos, CellType type);
        void OnLButtonDown(int mX, int mY);
        void OnRButtonDown(int mX, int mY);
        
    private:
        bool running;
        SDL_Window *mainWindow;
        SDL_Renderer *mainRenderer;
        Texture *animTexture;
        Animation animYoshi;
};

#endif