#include <SDLHandler.hpp>

SDLHandler::SDLHandler(int screenW, int screenH, int gridW, int gridH)
    : screenWidth(screenW), screenHeight(screenH),
      gridWidth(gridW), gridHeight(gridH)
{
    cellWidth = screenWidth / gridWidth;
    cellHeight = screenHeight / gridHeight;
}

SDLHandler::~SDLHandler() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SDLHandler::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL init failed: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("Ant Simulation",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screenWidth, screenHeight,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL window failed: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL renderer failed: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}


