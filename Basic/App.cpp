#include "App.h"
#include "Texture.h"

#define GRID_W 600
#define GRID_H 600
#define CELL_W 200
#define CELL_H 200
#define GRID_SIZE 9

App::App() : grid(GRID_SIZE, CellType::None), currentPlayer(Player::A) {
    mainWindow = NULL;
    mainRenderer = NULL;
    running = true;
    gridTexture = NULL;
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

    gridTexture = new Texture(mainRenderer, "gfx/grid.bmp");
    oTexture = new Texture(mainRenderer, "gfx/o.bmp", 255, 0, 255);
    xTexture = new Texture(mainRenderer, "gfx/x.bmp", 255, 0, 255);

    reset();

    return true;
}

void App::onEvent(SDL_Event* event) {
    Event::OnEvent(event);
}

void App::OnExit() {
    running = false;
}

void App::onLoop() {

}

void App::onRender() {
    
    if (mainRenderer != NULL) {

        SDL_RenderClear(mainRenderer);
        gridTexture->copyTo(mainRenderer);

        for (int i=0; i < GRID_SIZE; ++i) {

            int x = (i % 3) * CELL_W;
            int y = (i / 3) * CELL_H;
            
            if (grid[i] == CellType::X)
                xTexture->copyTo(mainRenderer, x, y);
            else if (grid[i] == CellType::O)
                oTexture->copyTo(mainRenderer, x, y);
        }
        
        SDL_RenderPresent(mainRenderer);
    }

    SDL_Delay(100);
}

void App::OnLButtonDown(int mX, int mY) {
    int pos = mX / CELL_W;
    pos = pos + ((mY / CELL_H) * 3);

    if (grid[pos] != CellType::None) {
        return;
    }

    if (currentPlayer == Player::A) {
        setCell(pos, CellType::X);
        currentPlayer = Player::B;
    } else {
        setCell(pos, CellType::O);
        currentPlayer = Player::A;
    }
}

void App::OnRButtonDown(int mX, int mY) {
    reset();
}

void App::onCleanup() {
    
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    
    SDL_Quit();
}

void App::reset() {
    for (auto& pos : grid)
        pos = CellType::None;
}

void App::setCell(int pos, CellType type) {
    if (pos < 0 || pos >= GRID_SIZE)
        return;

    grid[pos] = type;
}