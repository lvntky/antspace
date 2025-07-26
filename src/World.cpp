#include <World.hpp>
#include <data/Cell.hpp>

World::World(int width, int height) {
    
        }

    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

    void reset();
