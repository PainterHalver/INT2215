#ifndef CELL_H_
#define CELL_H_

#include <SDL.h>

class Cell {
    public:
    int i,j;
    double x,y,w,h;
    bool hasBomb = false;
    bool revealed = false;

    int neighborCount = 0;
    bool isHovered = false;
    Cell();

    Cell(int _i, int _j, double _x, double _y, double _w, double _h);

    void show(SDL_Renderer* renderer, SDL_Texture* bombTexture, SDL_Texture** numberTexture);

    void hover(SDL_Renderer* renderer);

    void unhover(SDL_Renderer* renderer);

    void reveal(Cell** grid, int ROWS, int COLS, SDL_Renderer* renderer, SDL_Texture* bombTexture, SDL_Texture** numberTexture, int &cellLeft);

};

void draw(SDL_Renderer* renderer);


#endif // CELL_H_
