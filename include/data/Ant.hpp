#ifndef ANT_HPP_
#define ANT_HPP_

#include <thread>

class Ant {
    private:
        int x;
        int y;
        bool carryingFood;
        int direction; // TODO: make enum
        std::thread::id ownerThreadId;
        // TODO: mutex
    public:
        Ant(int startX = 0, int startY = 0);
        ~Ant() = default;
};

#endif // ANT_H_
