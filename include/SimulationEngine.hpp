#ifndef SIMULATION_ENGINE_HPP_
#define SIMULATION_ENGINE_HPP_

#include <SDLHandler.hpp>
#include <data/Cell.hpp>
#include <vector>

class SimulationEngine {
public:
    SimulationEngine(int width, int height, int cellSize);
    void run();

private:
    int cols, rows;
    int cellSize;
    SDLHandler sdl;

    std::vector<std::vector<Cell>> grid;

    void handleEvents(bool& running);
    void update();
    void render();
};

#endif
