#include <iostream>
#include "initDep.h"
#include "gameControl.h"


using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    gameControl(renderer);

    quitSDL(window, renderer);
    return 0;
}


