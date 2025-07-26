#ifndef SDLHANDLER_HPP_
#define SDLHANDLER_HPP_

#include <SDL2/SDL.h>
#include <World.hpp>
#include <data/Ant.hpp>
#include <vector>

class SDLHandler {
    public:
       SDLHandler(int screenWidth, int screenHeight, int gridWidth, int gridHeight);
    ~SDLHandler();

    bool init();
    void clear();
    void drawWorld(const World& world);
    void drawAnts(const std::vector<Ant>& ants);
    void present();
    void handleEvents(bool& running);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int screenWidth;
    int screenHeight;
    int gridWidth;
    int gridHeight;

    int cellWidth;
    int cellHeight;

    void drawCell(int x, int y, float pheromoneLevel, float foodAmount);
    void drawAnt(int x, int y);
};

#endif //SDLHANDLER_HPP_

