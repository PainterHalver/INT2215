#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "initDep.h"
#include "imageLoader.h"

using namespace std;

class Cell {
    double x,y,w,h;
    bool hasBomb = true;
    bool revealed = true;
    public:
    Cell() {}

    Cell(double _x, double _y, double _w, double _h) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    void show(SDL_Renderer* renderer, SDL_Texture* bombTexture) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
        SDL_Rect rect = {x,y,w,h};
        SDL_RenderDrawRect(renderer, &rect);
        SDL_Rect smallRect = {x+5,y+5,w-8,h-8};
        if(this->revealed){
            if(this->hasBomb){
                SDL_RenderCopy(renderer, bombTexture, NULL, &smallRect);
            }
        }
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

    //init bomb img
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);
    SDL_RenderClear(renderer);
    SDL_Surface* bomb = SDL_LoadBMP("THE_mine.bmp");
    SDL_Texture* bombTexture = SDL_CreateTextureFromSurface(renderer, bomb);

    //SDL_Rect dstrect = {10,10,10,10};
    //SDL_RenderCopy(renderer, bombTexture, NULL, &dstrect);
    //SDL_RenderPresent(renderer);
    SDL_FreeSurface(bomb);


    //khoi tao grid
    Cell grid[ROWS][COLS];
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);   // white
    //SDL_RenderClear(renderer);
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            Cell temp(i*WIDTH+(SCREEN_WIDTH-COLS*WIDTH)/2, j*HEIGHT+(SCREEN_HEIGHT-ROWS*HEIGHT)/2, WIDTH, HEIGHT);
            grid[i][j] = temp;
            grid[i][j].show(renderer, bombTexture);
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


