#include <SimulationEngine.hpp>
#include <random>

SimulationEngine::SimulationEngine(int width, int height, int cellSize)
    : cellSize(cellSize),
      sdl(width, height, cellSize),
      cols(width / cellSize),
      rows(height / cellSize),
      grid(rows, std::vector<Cell>(cols)) {}

void SimulationEngine::run() {
    if (!sdl.init()) return;

    bool running = true;

    // Example: set food at (10,10) and ant at (5,5)
    grid[10][10].hasFood = true;
    grid[5][5].hasAnt = true;

    while (running) {
        sdl.handleEvents(running);
        update();
        render();
        SDL_Delay(100);
    }
}

void SimulationEngine::handleEvents(bool& running) {
    sdl.handleEvents(running);
}

void SimulationEngine::update() {
    // Example: decay pheromones
    for (auto& row : grid) {
        for (auto& cell : row) {
            if (cell.pheromone > 0.01f) {
                cell.pheromone *= 0.95f;
            } else {
                cell.pheromone = 0.0f;
            }
        }
    }
}

void SimulationEngine::render() {
    sdl.clear();
    sdl.drawGrid();

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            SDL_Color color = grid[y][x].getColor();
            if (!(color.r == 255 && color.g == 255 && color.b == 255)) {
                sdl.drawCell(x, y, color);
            }
        }
    }

    sdl.present();
}
