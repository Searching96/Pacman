#include "Pacman.h"

Pacman::Pacman(int _x, int _y, int _w, int _h, float _speed)
	: speed(_speed), dirX(0), dirY(0), posX(_x), posY(_y) {
	pmRect = { _x, _y, _w, _h };
}

void Pacman::handleEvent(SDL_Event& ev) {
	if (ev.type == SDL_KEYDOWN) {
		switch (ev.key.keysym.sym)
		{
		case SDLK_UP:
			dirX = 0;
			dirY = -1;
			break;
		case SDLK_DOWN:
			dirX = 0;
			dirY = 1;
			break;
		case SDLK_LEFT:
			dirX = -1;
			dirY = 0;
			break;
		case SDLK_RIGHT:
			dirX = 1;
			dirY = 0;
			break;
		default: // 
			break;
		}
	}
}

void Pacman::move(const vector<vector<int>>& map) {
	// Real pos
	float newX = posX + dirX * speed;
	float newY = posY + dirY * speed;

	// if move is valid, update new position
	if (isValidMove(newX, newY, map)) {
		posX = newX;
		posY = newY;
	}

	// set new position of pacman
	pmRect.x = static_cast<int>(posX);
	pmRect.y = static_cast<int>(posY);
}

bool Pacman::isValidMove(float newX, float newY, const vector<vector<int>>& map) {
	// tile index
	int leftX = static_cast<int>(newX) / TILE_SIZE;
	int rightX = static_cast<int>(newX + pmRect.w - 1) / TILE_SIZE;
	int topY = static_cast<int>(newY) / TILE_SIZE;
	int bottomY = static_cast<int>(newY + pmRect.h - 1) / TILE_SIZE;

	bool isValidMove = true;

	// check collision with top left, top right, bot left, bot right walls
	if (map[topY][leftX] == 1 || map[topY][rightX] == 1 || map[bottomY][leftX] == 1 || map[bottomY][rightX] == 1)
		isValidMove = false;

	return isValidMove;
}

void Pacman::render(SDL_Renderer* rd) {
	SDL_SetRenderDrawColor(rd, 255, 255, 0, 255);
	SDL_RenderFillRect(rd, &pmRect);
}

