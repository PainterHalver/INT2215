#include <iostream>
#include <SDL.h>
#include "initDep.h"

using namespace std;

class Cell {
    double x,y,w,h;
    public:
    Cell() {}

    Cell(double _x, double _y, double _w, double _h) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
        SDL_Rect rect;
        rect.w = w;
        rect.h = h;
        rect.x = x;
        rect.y = y;
        SDL_RenderDrawRect(renderer, &rect);

    }
};

void draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);   // white
    SDL_RenderClear(renderer);



    SDL_RenderPresent(renderer);
}

const int ROWS = 10;
const int COLS = 10;
const int WIDTH = 40;
const int HEIGHT = WIDTH;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //khoi tao grid
    Cell grid[ROWS][COLS];
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);   // white
    SDL_RenderClear(renderer);
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            Cell temp(i*WIDTH+(SCREEN_WIDTH-COLS*WIDTH)/2, j*HEIGHT+(SCREEN_HEIGHT-ROWS*HEIGHT)/2, WIDTH, HEIGHT);
            grid[i][j] = temp;
            grid[i][j].draw(renderer);
        }
    }
    SDL_RenderPresent(renderer);

    // Your drawing code here
    //draw(renderer);
    // use SDL_RenderPresent(renderer) to show it

	waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}


