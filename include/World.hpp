#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>
#include <data/Cell.hpp>

class World{
    private:
        int width;
        int height;
        std::vector<Cell> cells;

        int index(int x, int y) const;
    public:
        
        World(int width, int height);

    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

    void reset();
};

#endif //WORLD_HPP_
