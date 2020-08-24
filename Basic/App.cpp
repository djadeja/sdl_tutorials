#include "App.h"

App::App() {
    window = NULL;
    renderer = NULL;
    running = true;
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

    window = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if (window == NULL)
        return false;

    renderer = SDL_CreateRenderer(window, -1, 0);

    return true;
}

void App::onEvent(SDL_Event* event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }
}

void App::onLoop() {

}

void App::onRender() {
 
}

void App::onCleanup() {
    SDL_Quit();
}
