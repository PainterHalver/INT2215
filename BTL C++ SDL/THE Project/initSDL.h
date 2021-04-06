#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include "const.h"

const std::string WINDOW_TITLE = "Minesweeper";

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

