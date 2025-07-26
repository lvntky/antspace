#include <iostream>
#include <SDLHandler.hpp>
#include <data/Cell.hpp>

int main()
{
    std::cout << "Hello, world\n";
    Cell cell = Cell(100.0f, 100.0f);
    //std::mutex cellMutex = cell.getCellMutex();
    std::lock_guard<std::mutex> lock(cell.getCellMutex());
    
    
    return 0;
}
