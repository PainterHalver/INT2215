#include "Cell.h"
#include "const.h"
#include <time.h>

int betweenZeroAnd(int num) {
    return rand()*num/RAND_MAX;
}

bool check_click_in_rect(int x, int y, struct SDL_Rect *r) {
    return (x >= r->x) && (y >= r->y) && (x < r->x + r->w) && (y < r->y + r->h);
}

void gameControl(SDL_Renderer* &renderer) {
    srand(time(0));
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);
    SDL_RenderClear(renderer);
    //init imgs
    SDL_Surface* no1 = SDL_LoadBMP("1.bmp");
    SDL_Surface* no2 = SDL_LoadBMP("2.bmp");
    SDL_Surface* no3 = SDL_LoadBMP("3.bmp");
    SDL_Surface* no4 = SDL_LoadBMP("4.bmp");
    SDL_Surface* no5 = SDL_LoadBMP("5.bmp");
    SDL_Surface* no6 = SDL_LoadBMP("6.bmp");
    SDL_Surface* no7 = SDL_LoadBMP("7.bmp");
    SDL_Surface* no8 = SDL_LoadBMP("8.bmp");
    SDL_Surface* no9 = SDL_LoadBMP("THE_mine.bmp");
    SDL_Surface* playAgainButton = SDL_LoadBMP("PlayAgain.bmp");
    SDL_Texture* playAgainButtonTexture = SDL_CreateTextureFromSurface(renderer, playAgainButton);
    SDL_Texture* numberTexture[9];
    numberTexture[8] = SDL_CreateTextureFromSurface(renderer, no9);
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
    SDL_FreeSurface(no9);
    SDL_FreeSurface(no1);
    SDL_FreeSurface(no2);
    SDL_FreeSurface(no3);
    SDL_FreeSurface(no4);
    SDL_FreeSurface(no5);
    SDL_FreeSurface(no6);
    SDL_FreeSurface(no7);
    SDL_FreeSurface(no8);
    SDL_FreeSurface(playAgainButton);

    //khoi tao grid
    //Cell grid[ROWS][COLS];
    Cell **grid;
    grid = new Cell *[ROWS];
    for(int i = 0; i <ROWS; i++){
        grid[i] = new Cell[COLS];
    }


    srand(time(0));
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            Cell temp(i, j, i*WIDTH+GRID_START_X, j*HEIGHT+GRID_START_Y, WIDTH-1, HEIGHT-1);
            grid[i][j] = temp;
            grid[i][j].show(renderer, numberTexture[8], numberTexture);
        }
    }
    //SPREAD THE BOMBS
    int bombCreated = 0;
    while(bombCreated < TOTALBOMBS) {
        int i = betweenZeroAnd(ROWS);
        int j = betweenZeroAnd(COLS);
        if(grid[i][j].hasBomb == false) {
            grid[i][j].hasBomb = true;
            grid[i][j].neighborCount = -1;
            bombCreated++;
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
    /*
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            grid[i][j].show(renderer, bombTexture, numberTexture);
        }
    } */

    //Always keep the "play again" button
    SDL_Rect playAgainRect = {10, 10,107,29}; // Positioning the button
    SDL_RenderCopy(renderer, playAgainButtonTexture, NULL, &playAgainRect);

    SDL_Event e;
    bool isRunning = true;
    Cell* curHover = new Cell;
    SDL_RenderPresent(renderer);
    while (isRunning){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT){
                isRunning = false;
                break;
            }
            else if (e.type == SDL_MOUSEMOTION){
                double x = e.button.x;
                double y = e.button.y;
                if(x > GRID_START_X && x < GRID_START_X+GRID_WIDTH && y > GRID_START_Y && y < GRID_START_Y+GRID_HEIGHT){
                    curHover->unhover(renderer);
                    curHover = &grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT];
                    curHover->hover(renderer);
                    SDL_RenderPresent(renderer);
                } //else { //lag
                    //curHover->unhover(renderer);
                   // SDL_RenderPresent(renderer);
                //}
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                double x = e.button.x;
                double y = e.button.y;
                if(x > GRID_START_X && x < GRID_START_X+GRID_WIDTH && y > GRID_START_Y && y < GRID_START_Y+GRID_HEIGHT){
                    if(!(grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT].hasBomb)){
                       grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT].reveal(grid, ROWS, COLS, renderer, numberTexture[8], numberTexture);
                    } else {
                        for(int i = 0; i < ROWS; ++i) {
                            for(int j = 0; j < COLS; ++j) {
                                grid[i][j].reveal(grid, ROWS, COLS, renderer, numberTexture[8], numberTexture);
                            }
                        }
                    }
                } else if(check_click_in_rect(x,y, &playAgainRect)){
                    delete [] grid;
                    return gameControl(renderer);
                }
            }
        }
    }
    delete [] grid;
}
