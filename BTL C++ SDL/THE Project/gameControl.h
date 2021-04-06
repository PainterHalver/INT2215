#ifndef GAMECONTROL_H_
#define GAMECONTROL_H_

#include "Cell.h"
#include "const.h"
#include <time.h>

int betweenZeroAnd(int num);

bool check_click_in_rect(int x, int y, struct SDL_Rect *r);

void gameControl(SDL_Renderer* &renderer);

#endif // GAMECONTROL_H_
