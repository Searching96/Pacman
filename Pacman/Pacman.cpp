#include "Pacman.h"

Pacman::Pacman(int _x, int _y, int _w, int _h, int _speed)
	: x(_x), y(_y), w(_w), h(_h), speed(_speed) {}

void Pacman::move(SDL_Event& ev) {
	if (ev.type == SDL_KEYDOWN) {
		switch (ev.key.keysym.sym)
		{
		case SDLK_UP:
			y -= speed;
			break;
		case SDLK_DOWN:
			y += speed;
			break;
		case SDLK_LEFT:
			x -= speed;
			break;
		case SDLK_RIGHT:
			x += speed;
			break;
		default: // 
			break;
		}
	}
}

void Pacman::render(SDL_Renderer* rd) {
	SDL_Rect fillRect = { x, y, w, h };
	SDL_SetRenderDrawColor(rd, 255, 255, 0, 255);
	SDL_RenderFillRect(rd, &fillRect);
}

