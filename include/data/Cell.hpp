#ifndef CELL_HPP
#define CELL_HPP

#include <SDL2/SDL.h>

struct Cell {
    bool hasFood = false;
    bool hasAnt = false;
    float pheromone = 0.0f;

    SDL_Color getColor() const {
        if (hasAnt) return {0, 0, 0, 255};         // black for ant
        if (hasFood) return {0, 255, 0, 255};      // green for food
        if (pheromone > 0.01f) return {255, 0, 255, 255}; // pink for pheromone
        return {255, 255, 255, 255};               // white
    }
};

#endif
