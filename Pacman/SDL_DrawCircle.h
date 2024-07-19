#pragma once
#include <cmath>
#include <SDL.h>

using namespace std;

void drawPoint(SDL_Renderer* rd, int x, int y);
void SDL_RenderDrawCircle(SDL_Renderer* rd, float centerX, float centerY, int radius);
void SDL_RenderDrawFilledCircle(SDL_Renderer* rd, float x, float y, int radius, SDL_Color color);