#include "gameControl.h"

int betweenZeroAnd(int num) {
    return rand()*num/RAND_MAX;
}

bool check_click_in_rect(int x, int y, struct SDL_Rect *r) {
    return (x >= r->x) && (y >= r->y) && (x < r->x + r->w) && (y < r->y + r->h);
}

bool checkSurround(int i, int j, Cell **grid){
    for(int xoff = -1; xoff <=1; ++xoff) {
        for(int yoff = -1; yoff <=1; ++yoff) {
            int k = i+xoff;
            int l = j+yoff;
            if(k > -1 && k < ROWS && l > -1 && l < COLS && xoff != 0 && yoff != 0){
                int total = 0;
                for(int xoff2 = -1; xoff2 <=1; ++xoff2) {
                    for(int yoff2 = -1; yoff2 <=1; ++yoff2) {
                        int x = grid[k][l].i+xoff2;
                        int z = grid[k][l].j+yoff2;
                        if(x > -1 && x < ROWS && z > -1 && z < COLS && xoff2 != 0 && yoff2 != 0){
                            if(grid[x][z].hasBomb) {
                                total++;
                            }
                        }
                    }
                }
                if (total >= 4) {return false;}
            }
        }
    }
    return true;
}

Cell** initGrid(SDL_Renderer* &renderer, SDL_Texture* mineTexture, SDL_Texture** numberTexture){
    //Cell grid[ROWS][COLS];
    Cell **grid;
    grid = new Cell *[ROWS];
    for(int i = 0; i <ROWS; i++){
        grid[i] = new Cell[COLS];
    }

    //render start grid
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            Cell temp(i, j, i*WIDTH+GRID_START_X, j*HEIGHT+GRID_START_Y, WIDTH-1, HEIGHT-1);
            grid[i][j] = temp;
            grid[i][j].show(renderer, mineTexture, numberTexture);
        }
    }

    //SPREAD THE BOMBS
    int bombCreated = 0;
    while(bombCreated < TOTALBOMBS) {
        int i = betweenZeroAnd(ROWS);
        int j = betweenZeroAnd(COLS);
        if(!(grid[i][j].hasBomb) && checkSurround(i,j, grid)){
            grid[i][j].hasBomb = true;
            grid[i][j].neighborCount = -1;
            bombCreated++;
        }
    }

    // COUNT NEIGHBORS and ASSIGN TO CELL
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
    return grid;
}

void gameControl(SDL_Renderer* &renderer) {
    srand(time(0));
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);
    SDL_RenderClear(renderer);

    //INIT IMGS
    SDL_Surface* no1 = SDL_LoadBMP("1.bmp");
    SDL_Surface* no2 = SDL_LoadBMP("2.bmp");
    SDL_Surface* no3 = SDL_LoadBMP("3.bmp");
    SDL_Surface* no4 = SDL_LoadBMP("4.bmp");
    SDL_Surface* no5 = SDL_LoadBMP("5.bmp");
    SDL_Surface* no6 = SDL_LoadBMP("6.bmp");
    SDL_Surface* no7 = SDL_LoadBMP("7.bmp");
    SDL_Surface* no8 = SDL_LoadBMP("8.bmp");
    SDL_Surface* mine = SDL_LoadBMP("THE_mine.bmp");
    SDL_Surface* youwin = SDL_LoadBMP("youwin.bmp");
    SDL_Surface* playAgainButton = SDL_LoadBMP("PlayAgain.bmp");

    SDL_Texture* playAgainButtonTexture = SDL_CreateTextureFromSurface(renderer, playAgainButton);
    SDL_Texture* mineTexture = SDL_CreateTextureFromSurface(renderer, mine);
    SDL_Texture* youwinTexture = SDL_CreateTextureFromSurface(renderer, youwin);

    SDL_Texture* numberTexture[8];
    numberTexture[0] = SDL_CreateTextureFromSurface(renderer, no1);
    numberTexture[1] = SDL_CreateTextureFromSurface(renderer, no2);
    numberTexture[2] = SDL_CreateTextureFromSurface(renderer, no3);
    numberTexture[3] = SDL_CreateTextureFromSurface(renderer, no4);
    numberTexture[4] = SDL_CreateTextureFromSurface(renderer, no5);
    numberTexture[5] = SDL_CreateTextureFromSurface(renderer, no6);
    numberTexture[6] = SDL_CreateTextureFromSurface(renderer, no7);
    numberTexture[7] = SDL_CreateTextureFromSurface(renderer, no8);

    SDL_FreeSurface(no1);
    SDL_FreeSurface(no2);
    SDL_FreeSurface(no3);
    SDL_FreeSurface(no4);
    SDL_FreeSurface(no5);
    SDL_FreeSurface(no6);
    SDL_FreeSurface(no7);
    SDL_FreeSurface(no8);
    SDL_FreeSurface(mine);    SDL_FreeSurface(youwin);
    SDL_FreeSurface(playAgainButton);

    //INIT GRID
    Cell **grid = initGrid(renderer, mineTexture, numberTexture);

    //Always keep the "play again" button
    SDL_Rect playAgainRect = {10, 10,107,29}; // Positioning the button
    SDL_RenderCopy(renderer, playAgainButtonTexture, NULL, &playAgainRect);

    SDL_Event e;
    bool isRunning = true;
    Cell* curHover = new Cell;
    SDL_RenderPresent(renderer);
    int waittime = 1000.0f/FPS;
    int framestarttime = 0;
    int delaytime;
    int cellLeft = ROWS*COLS;

    //MAIN LOOP
    while (isRunning){
        // CHECK WIN
        if(cellLeft == TOTALBOMBS){
            SDL_Rect rect = {300,10,200, 30};
            SDL_RenderCopy(renderer, youwinTexture, NULL, &rect);
        }
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT){
                isRunning = false;
                break;
            }
            //MOUSE EVENTS
            else if (e.type == SDL_MOUSEMOTION){
                //HOVER CELL
                double x = e.button.x;
                double y = e.button.y;
                curHover->unhover(renderer);
                if(x > GRID_START_X && x < GRID_START_X+GRID_WIDTH && y > GRID_START_Y && y < GRID_START_Y+GRID_HEIGHT){
                    curHover->unhover(renderer);
                    curHover = &grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT];
                    curHover->hover(renderer);
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                double x = e.button.x;
                double y = e.button.y;
                if(x > GRID_START_X && x < GRID_START_X+GRID_WIDTH && y > GRID_START_Y && y < GRID_START_Y+GRID_HEIGHT){
                    if(!(grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT].hasBomb)){
                       grid[(int)(x-GRID_START_X)/WIDTH][(int)(y-GRID_START_Y)/HEIGHT].reveal(grid, ROWS, COLS, renderer, mineTexture, numberTexture, cellLeft);
                    } else {
                        for(int i = 0; i < ROWS; ++i) {
                            for(int j = 0; j < COLS; ++j) {
                                grid[i][j].reveal(grid, ROWS, COLS, renderer, mineTexture, numberTexture, cellLeft);
                            }
                        }
                    }
                } else if(check_click_in_rect(x,y, &playAgainRect)){
                    delete [] grid;
                    return gameControl(renderer);
                }
            }
        }
        SDL_RenderPresent(renderer);

        //SET FPS DELAY
        delaytime = waittime - (SDL_GetTicks() - framestarttime);
        if(delaytime > 0)
            SDL_Delay((int)delaytime);
        framestarttime = SDL_GetTicks();
    }
    delete [] grid;
}
