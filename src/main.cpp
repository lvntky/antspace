#include <iostream>
#include <SDLHandler.hpp>
#include <SimulationEngine.hpp>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int cellSize = 20;

    SimulationEngine engine(screenWidth, screenHeight, cellSize);
    engine.run();
    
    return 0;
}
