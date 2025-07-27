#ifndef SDL_HANDLER_HPP_
#define SDL_HANDLER_HPP_

#include <SDL2/SDL.h>
#include <vector>

class SDLHandler {
public:
    SDLHandler(int width, int height, int cellSize);
    ~SDLHandler();

    bool init();
    void clear();
    void drawGrid();
    void drawCell(int x, int y, SDL_Color color);
    void present();
    void handleEvents(bool &running);

private:
    int width;
    int height;
    int cellSize;

    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // SDL_HANDLER_HPP_
