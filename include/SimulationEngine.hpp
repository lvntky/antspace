#ifndef SIMULATION_ENGINE_HPP_
#define SIMULATION_ENGINE_HPP_

class SimulationEngine {
    private:
        int worldWidth;
        int worldHeight;
        int numAnts;
        bool running = false;

        void mainLoop();

    public:
        void run();
        void stop();
        bool isRunning();
        SimulationEngine(int width, int height, int numAnts);
        
};

#endif //SIMULATION_ENGINE_HPP_
