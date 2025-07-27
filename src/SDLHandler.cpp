#include <SDLHandler.hpp>
#include <iostream>
#include <config.h>

SDLHandler::SDLHandler(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize),
      window(nullptr), renderer(nullptr) {}

SDLHandler::~SDLHandler() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SDLHandler::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(C_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

void SDLHandler::clear() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White background
    SDL_RenderClear(renderer);
}

void SDLHandler::drawGrid() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Light gray

    for (int x = 0; x < width; x += cellSize) {
        SDL_RenderDrawLine(renderer, x, 0, x, height);
    }

    for (int y = 0; y < height; y += cellSize) {
        SDL_RenderDrawLine(renderer, 0, y, width, y);
    }
}

void SDLHandler::drawCell(int x, int y, SDL_Color color) {
    SDL_Rect rect = { x * cellSize, y * cellSize, cellSize, cellSize };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void SDLHandler::present() {
    SDL_RenderPresent(renderer);
}

void SDLHandler::handleEvents(bool &running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            running = false;
    }
}
