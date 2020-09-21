#include "App.h"
#include "Texture.h"
#include "Define.h"
#include "Camera.h"
#include "Area.h"
#include "FPS.h"

#define CELL_W 200
#define CELL_H 200
#define GRID_SIZE 9

App::App() {
    mainWindow = NULL;
    mainRenderer = NULL;
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

    mainWindow = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 0);

    if (mainWindow == NULL)
        return false;

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (player.onLoad(mainRenderer, "gfx/yoshi.png", 64, 64, 8) == false)
        return false;
    
    if (player2.onLoad(mainRenderer, "gfx/yoshi.png", 64, 64, 8) == false)
        return false;
        
    player2.x = 100;

    Entity::entityList.push_back(&player);
    Entity::entityList.push_back(&player2);

    if (Area::areacontrol.onLoad(mainRenderer, "./maps/1.area") == false) {
        return false;
    }
 
    Camera::cameraControl.targetMode = TargetMode::CENTER;
    Camera::cameraControl.setTarget(&player.x, &player.y);

    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    return true;
}

void App::onEvent(SDL_Event* event) {
    Event::OnEvent(event);
}

void App::OnExit() {
    running = false;
}

void App::onLoop() {
    for (auto entity : Entity::entityList) {
        if (entity == NULL)
            continue;
        entity->onLoop();        
    }
    FPS::FPSControl.OnLoop();
}

void App::onRender() {
    
    if (mainRenderer != NULL) {

        SDL_RenderClear(mainRenderer);

        Area::areacontrol.onRender(mainRenderer, -Camera::cameraControl.getX(), -Camera::cameraControl.getY());

        for (auto entity : Entity::entityList) {
            if (entity == NULL)
                continue;
            entity->onRender(mainRenderer);
        }

        SDL_RenderPresent(mainRenderer);
    }

    //SDL_Delay(1);
}

void App::OnLButtonDown(int mX, int mY) {
   
}

void App::OnRButtonDown(int mX, int mY) {
    
}

void App::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
   switch(sym) {
        case SDLK_LEFT: {
            player.MoveLeft = true;
            break;
        }
 
        case SDLK_RIGHT: {
            player.MoveRight = true;
            break;
        }
 
        default: {
        }
    }
}

void App::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
   switch(sym) {
        case SDLK_LEFT: {
            player.MoveLeft = false;
            break;
        }
 
        case SDLK_RIGHT: {
            player.MoveRight = false;
            break;
        }
 
        default: {
        }
    }
}

void App::onCleanup() {
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);

    for (auto entity : Entity::entityList) {
        if (entity == NULL)
            continue;
        entity->onCleanup();
    }
    Entity::entityList.clear();

    Area::areacontrol.onCleanup();
    
    SDL_Quit();
}
