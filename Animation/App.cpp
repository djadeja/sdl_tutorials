#include "App.h"
#include "Texture.h"

#define GRID_W 600
#define GRID_H 600
#define CELL_W 200
#define CELL_H 200
#define GRID_SIZE 9

App::App() {
    mainWindow = NULL;
    mainRenderer = NULL;
    running = true;
    animTexture = NULL;
}

int App::onExecute() {
    if (onInit() == false) {
        return -1;
    }

    SDL_Event event;
    while(running) {

        while(SDL_PollEvent(&event)) {
            onEvent(&event);
        }

        onLoop();
        onRender();
    }

    onCleanup();

    return 0;
}

bool App::onInit() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    mainWindow = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GRID_W, GRID_H, 0);

    if (mainWindow == NULL)
        return false;

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    animTexture = new Texture(mainRenderer, "gfx/yoshi.bmp", 255, 0, 255);

    animYoshi.maxFrames = 8;
    animYoshi.oscillate = false;
    
    return true;
}

void App::onEvent(SDL_Event* event) {
    Event::OnEvent(event);
}

void App::OnExit() {
    running = false;
}

void App::onLoop() {
    animYoshi.onAnimate();
}

void App::onRender() {
    
    if (mainRenderer != NULL) {

        SDL_RenderClear(mainRenderer);

        animTexture->copyTo(mainRenderer, 200, 200, 0, animYoshi.getCurrentFrame() * 64, 64, 64); 

        SDL_RenderPresent(mainRenderer);
    }

    SDL_Delay(1);
}

void App::OnLButtonDown(int mX, int mY) {
   
}

void App::OnRButtonDown(int mX, int mY) {
    
}

void App::onCleanup() {
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    
    SDL_Quit();
}
