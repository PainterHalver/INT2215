#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "initDep.h"
#include "imageLoader.h"

using namespace std;

class Cell {
    public:
    int i,j;
    double x,y,w,h;
    bool hasBomb = (double)rand()/RAND_MAX < 0.5 ? true : false;
    bool revealed = false;

    int neighborCount = 0;
    bool isHovered = false;
    Cell() {}

    Cell(int _i, int _j, double _x, double _y, double _w, double _h) {
        i = _i;
        j = _j;
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    void show(SDL_Renderer* renderer, SDL_Texture* bombTexture, SDL_Texture** numberTexture) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
        SDL_Rect rect = {x,y,w,h};
        SDL_RenderDrawRect(renderer, &rect);
        SDL_Rect smallRect = {x+1.3,y+1.3,w-2,h-2};
        if(this->revealed){
            if(this->hasBomb){
                SDL_RenderCopy(renderer, bombTexture, NULL, &smallRect);
            } else if(this->neighborCount!=0) {
                SDL_RenderCopy(renderer, numberTexture[neighborCount-1], NULL, &smallRect);
            } else if(this-> neighborCount==0) {
                SDL_SetRenderDrawColor(renderer, 245, 215, 110, 255);   // yellow
                SDL_RenderFillRect(renderer, &smallRect);
            }
        }
    }

    void hover(SDL_Renderer* renderer){
        if(revealed || isHovered) return;
        this->isHovered = true;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 128);   // not so black
        SDL_Rect smallRect = {x+1.3,y+1.3,w-2,h-2};
        SDL_RenderFillRect(renderer, &smallRect);
    }

    void unhover(SDL_Renderer* renderer){
        if(revealed || !isHovered) return;
        this->isHovered = false;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
        SDL_Rect smallRect = {x+1.3,y+1.3,w-2,h-2};
        SDL_RenderFillRect(renderer, &smallRect);
    }

    Cell* reveal(){
        this->revealed = true;
    }

};

void draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);   // white
    SDL_RenderClear(renderer);



    SDL_RenderPresent(renderer);
}

/*
void eventManager(SDL_Renderer* renderer) {
    SDL_Event e;
    bool isRunning = true;
    while (isRunning){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT){
                isRunning = false;
            }
            else if (e.type == SDL_MOUSEMOTION){
                e.button.x
            }
        }
    }
}
*/

const int ROWS = 10;
const int COLS = 10;
const int WIDTH = 40;
const int HEIGHT = WIDTH;
const double GRID_START_X = (double)(SCREEN_WIDTH-COLS*WIDTH)/2;
const double GRID_START_Y = (double)(SCREEN_HEIGHT-ROWS*HEIGHT)/2;
const double GRID_WIDTH = COLS*WIDTH;
const double GRID_HEIGHT = ROWS*HEIGHT;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //init bomb img
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);
    SDL_RenderClear(renderer);
    SDL_Surface* bomb = SDL_LoadBMP("THE_mine.bmp");
    SDL_Surface* no1 = SDL_LoadBMP("1.bmp");
    SDL_Surface* no2 = SDL_LoadBMP("2.bmp");
    SDL_Surface* no3 = SDL_LoadBMP("3.bmp");
    SDL_Surface* no4 = SDL_LoadBMP("4.bmp");
    SDL_Surface* no5 = SDL_LoadBMP("5.bmp");
    SDL_Surface* no6 = SDL_LoadBMP("6.bmp");
    SDL_Surface* no7 = SDL_LoadBMP("7.bmp");
    SDL_Surface* no8 = SDL_LoadBMP("8.bmp");
    SDL_Texture* bombTexture = SDL_CreateTextureFromSurface(renderer, bomb);
    SDL_Texture* numberTexture[8];
    numberTexture[0] = SDL_CreateTextureFromSurface(renderer, no1);
    numberTexture[1] = SDL_CreateTextureFromSurface(renderer, no2);
    numberTexture[2] = SDL_CreateTextureFromSurface(renderer, no3);
    numberTexture[3] = SDL_CreateTextureFromSurface(renderer, no4);
    numberTexture[4] = SDL_CreateTextureFromSurface(renderer, no5);
    numberTexture[5] = SDL_CreateTextureFromSurface(renderer, no6);
    numberTexture[6] = SDL_CreateTextureFromSurface(renderer, no7);
    numberTexture[7] = SDL_CreateTextureFromSurface(renderer, no8);

    //SDL_Rect dstrect = {10,10,10,10};
    //SDL_RenderCopy(renderer, bombTexture, NULL, &dstrect);
    //SDL_RenderPresent(renderer);
    SDL_FreeSurface(bomb);
    SDL_FreeSurface(no1);
    SDL_FreeSurface(no2);
    SDL_FreeSurface(no3);
    SDL_FreeSurface(no4);
    SDL_FreeSurface(no5);
    SDL_FreeSurface(no6);
    SDL_FreeSurface(no7);
    SDL_FreeSurface(no8);


    //khoi tao grid
    Cell grid[ROWS][COLS];
    srand(time(0));

    //SDL_RenderClear(renderer);
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            Cell temp(i, j, i*WIDTH+GRID_START_X, j*HEIGHT+GRID_START_Y, WIDTH-1, HEIGHT-1);
            grid[i][j] = temp;
            grid[i][j].show(renderer, bombTexture, numberTexture);
        }
    }
    // PUBLIC ALL KEKW BCUZ OF THIS
    // COUNT NEIGHBORS
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            if(grid[i][j].hasBomb) continue;
            int total = 0;
             for(int xoff = -1; xoff <=1; ++xoff) {
                for(int yoff = -1; yoff <=1; ++yoff) {
                    int k = grid[i][j].i+xoff;
                    int l = grid[i][j].j+yoff;
                    if(k > -1 && k < ROWS && l > -1 && l < COLS){
                        if(grid[k][l].hasBomb) {
                            total++;
                        }
                    }
                }
            }
            grid[i][j].neighborCount = total;
        }
    }
    /*for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            grid[i][j].show(renderer, bombTexture, numberTexture);
        }
    }*/

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool isRunning = true;
    Cell* curHover = new Cell;
    while (isRunning){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT){
                isRunning = false;
            }
            else if (e.type == SDL_MOUSEMOTION){
                double x = e.button.x;
                double y = e.button.y;
                if(x > GRID_START_X && x < GRID_START_X+GRID_WIDTH && y > GRID_START_Y && y < GRID_START_Y+GRID_HEIGHT){
                    curHover->unhover(renderer);
                    curHover = &grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT];
                    curHover->hover(renderer);
                    SDL_RenderPresent(renderer);
                } //else { //lag wa
                    //curHover->unhover(renderer);
                   // SDL_RenderPresent(renderer);
                //}
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                double x = e.button.x;
                double y = e.button.y;
                if(x > GRID_START_X && x < GRID_START_X+GRID_WIDTH && y > GRID_START_Y && y < GRID_START_Y+GRID_HEIGHT){
                    grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT].reveal()->show(renderer, bombTexture, numberTexture);
                }
            }
        }
    }

    // Your drawing code here
    //draw(renderer);
    // use SDL_RenderPresent(renderer) to show it

	//waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}


