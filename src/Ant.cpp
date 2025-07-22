#include <data/Ant.hpp>

Ant::Ant(int startX, int startY) {
    this->x = startX;
    this->y = startY;
    this->direction = 0;
    this->ownerThreadId = std::this_thread::get_id();
}
