#include <SDLHandler.hpp>
#include <iostream>
#include <algorithm>

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

void SDLHandler::clear() {
    // Set background to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLHandler::drawWorld(const World& world) {
    for (int x = 0; x < world.getWidth(); ++x) {
        for (int y = 0; y < world.getHeight(); ++y) {
            const Cell& cell = world.getCell(x, y);
            
            // Assuming Cell has getPheromoneLevel() and getFoodAmount() methods
            // You'll need to adjust these method names based on your Cell implementation
            float pheromoneLevel = 0.0f; // cell.getPheromoneLevel();
            float foodAmount = 0.0f;     // cell.getFoodAmount();
            
            drawCell(x, y, pheromoneLevel, foodAmount);
        }
    }
}

void SDLHandler::drawAnts(const std::vector<Ant>& ants) {
    for (const auto& ant : ants) {
        // Assuming Ant has getX() and getY() methods
        // You'll need to add these getter methods to your Ant class
        int antX = 0; // ant.getX();
        int antY = 0; // ant.getY();
        
        drawAnt(antX, antY);
    }
}

void SDLHandler::present() {
    SDL_RenderPresent(renderer);
}

void SDLHandler::handleEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                break;
        }
    }
}

void SDLHandler::drawCell(int x, int y, float pheromoneLevel, float foodAmount) {
    SDL_Rect cellRect;
    cellRect.x = x * cellWidth;
    cellRect.y = y * cellHeight;
    cellRect.w = cellWidth;
    cellRect.h = cellHeight;
    
    // Base color (dark gray for empty cells)
    Uint8 r = 32, g = 32, b = 32;
    
    // Color based on food amount (green tint)
    if (foodAmount > 0.0f) {
        float foodIntensity = std::min(foodAmount, 1.0f);
        r = static_cast<Uint8>(32 + foodIntensity * 100);
        g = static_cast<Uint8>(32 + foodIntensity * 200);
        b = static_cast<Uint8>(32);
    }
    
    // Color based on pheromone level (blue tint)
    if (pheromoneLevel > 0.0f) {
        float pheromoneIntensity = std::min(pheromoneLevel, 1.0f);
        r = static_cast<Uint8>(std::max(static_cast<int>(r), static_cast<int>(32 + pheromoneIntensity * 50)));
        g = static_cast<Uint8>(std::max(static_cast<int>(g), static_cast<int>(32 + pheromoneIntensity * 50)));
        b = static_cast<Uint8>(std::max(static_cast<int>(b), static_cast<int>(32 + pheromoneIntensity * 200)));
    }
    
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &cellRect);
    
    // Draw grid lines (optional, for better visibility)
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    SDL_RenderDrawRect(renderer, &cellRect);
}

void SDLHandler::drawAnt(int x, int y) {
    SDL_Rect antRect;
    antRect.x = x * cellWidth + cellWidth / 4;
    antRect.y = y * cellHeight + cellHeight / 4;
    antRect.w = cellWidth / 2;
    antRect.h = cellHeight / 2;
    
    // Draw ant as a red circle (approximated with a filled rectangle)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &antRect);
    
    // Draw a smaller inner circle for better visibility
    SDL_Rect innerRect;
    innerRect.x = antRect.x + antRect.w / 4;
    innerRect.y = antRect.y + antRect.h / 4;
    innerRect.w = antRect.w / 2;
    innerRect.h = antRect.h / 2;
    
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(renderer, &innerRect);
}
