#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>
#include "Event.h"
#include "Entity.h"
#include "Player.h"

#include <vector>

using namespace std;

class Texture;

enum class CellType {
            None,
            X,
            O
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
        void OnKeyDown(SDL_Keycode sym, Uint16 mod);
        void OnKeyUp(SDL_Keycode sym, Uint16 mod);
        
    private:
        bool running;
        SDL_Window *mainWindow;
        SDL_Renderer *mainRenderer;
        Player  player;
        Player  player2;
};

#endif