#ifndef CELL_HPP_
#define CELL_HPP_

#include <mutex>

class Cell {
    private:
        float foodAmount;
        float pheromoneLevel;
        mutable std::mutex cellMutex;
    public:
        Cell(float foodAmountStart, float pheromoneLevelStart);
        std::mutex& getCellMutex();
};

#endif // CELL_HPP_
