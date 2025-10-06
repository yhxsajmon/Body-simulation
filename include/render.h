#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include "Body.h"

void drawBody(BodyPtr body, SDL_Renderer* renderer);
void plotCirclePoints(SDL_Renderer* renderer, int cx, int cy, int x, int y);
//void initRender(SDL_Window* window);

#endif