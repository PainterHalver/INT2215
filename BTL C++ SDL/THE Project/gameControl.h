#ifndef GAMECONTROL_H_
#define GAMECONTROL_H_

#include "Cell.h"
#include "const.h"
#include <time.h>

int betweenZeroAnd(int num);

bool check_click_in_rect(int x, int y, struct SDL_Rect *r);

bool checkSurround(int i, int j, Cell **grid);

void gameControl(SDL_Renderer* &renderer);

#endif // GAMECONTROL_H_
