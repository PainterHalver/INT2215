#include "Cell.h"

Cell::Cell() {}

Cell::Cell(int _i, int _j, double _x, double _y, double _w, double _h) {
    i = _i;
    j = _j;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Cell::show(SDL_Renderer* renderer, SDL_Texture* bombTexture, SDL_Texture** numberTexture) {
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

void Cell::hover(SDL_Renderer* renderer){
    if(revealed || isHovered) return;
    this->isHovered = true;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 128);   // not so black
    SDL_Rect smallRect = {x+1.3,y+1.3,w-2,h-2};
    SDL_RenderFillRect(renderer, &smallRect);
}

void Cell::unhover(SDL_Renderer* renderer){
    if(revealed || !isHovered) return;
    this->isHovered = false;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_Rect smallRect = {x+1.3,y+1.3,w-2,h-2};
    SDL_RenderFillRect(renderer, &smallRect);
}

void Cell::reveal(Cell** grid, int ROWS, int COLS, SDL_Renderer* renderer, SDL_Texture* bombTexture, SDL_Texture** numberTexture, int &cellLeft){
    if(this->revealed) return;
    this->revealed = true;
    this->show(renderer, bombTexture, numberTexture);
    cellLeft = cellLeft - 1;
    if(this->neighborCount == 0){
        for(int xoff = -1; xoff <=1; ++xoff) {
            for(int yoff = -1; yoff <=1; ++yoff) {
                int k = this->i+xoff;
                int l = this->j+yoff;
                if(k > -1 && k < ROWS && l > -1 && l < COLS){
                    if(!(grid[k][l].hasBomb) && !(grid[k][l].revealed)) {
                        grid[k][l].reveal(grid, ROWS, COLS, renderer, bombTexture, numberTexture, cellLeft);
                    }
                }
            }
        }
    }
}

void draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);   // white
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
