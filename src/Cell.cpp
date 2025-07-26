#include <data/Cell.hpp>

Cell::Cell(float foodAmountStart, float pheromoneLevelStart) {
    this->foodAmount = foodAmountStart;
    this->pheromoneLevel = pheromoneLevelStart;
//    this->cellMutex = std::mutex();
  //  this->cellMutex = cellMutex.unlock();
}

std::mutex& Cell::getCellMutex() {
    return this->cellMutex;
}
