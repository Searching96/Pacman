#include "Pacman.h"

Pacman::Pacman(int _x, int _y, int _w, int _h, float _speed)
	: speed(_speed), dirX(0), dirY(0), posX(_x), posY(_y), tempDirX(0), tempDirY(0) {
	pmRect = { _x, _y, _w, _h };
}

void Pacman::handleEvent(SDL_Event& ev) {
	if (ev.type == SDL_KEYDOWN) {
		switch (ev.key.keysym.sym) {
		case SDLK_UP:
			tempDirX = 0;
			tempDirY = -1;
			break;
		case SDLK_DOWN:
			tempDirX = 0;
			tempDirY = 1;
			break;
		case SDLK_LEFT:
			tempDirX = -1;
			tempDirY = 0;
			break;
		case SDLK_RIGHT:
			tempDirX = 1;
			tempDirY = 0;
			break;
		default: //
			break;
		}
	}
}

void Pacman::move(const vector<vector<int>>& map) {
    // Real pos with temporary direction
    float tempNewX = posX + tempDirX * speed;
    float tempNewY = posY + tempDirY * speed;

    // Wrap around logic for temporary position
    wrapAround(tempNewX, tempNewY);

    // Check if temporary direction is valid
    if (isValidMove(tempNewX, tempNewY, map)) {
        dirX = tempDirX;
        dirY = tempDirY;
    }

    // Real pos with current direction
    float newX = posX + dirX * speed;
    float newY = posY + dirY * speed;

    // Wrap around logic for new position
    wrapAround(newX, newY);

    // If move is valid, update position
    if (isValidMove(newX, newY, map)) {
        posX = newX;
        posY = newY;
    }
    else {
        // Additional wrap around to prevent being stuck at the boundary
        wrapAround(posX, posY);
    }

    // Update SDL_Rect position
    pmRect.x = static_cast<int>(posX);
    pmRect.y = static_cast<int>(posY);
}

void Pacman::wrapAround(float& x, float& y) {
    if (x < 0) x = MAP_WIDTH - 1;
    if (x >= MAP_WIDTH) x = 0;
    if (y < 0) y = MAP_HEIGHT - 1;
    if (y >= MAP_HEIGHT) y = 0;
}

bool Pacman::isValidMove(float newX, float newY, const vector<vector<int>>& map) {
    // Tính toán các ch? s? c?a các ?i?m xung quanh Pacman
    int leftX = static_cast<int>(newX) / TILE_SIZE;
    int rightX = static_cast<int>(newX + pmRect.w - 1) / TILE_SIZE;
    int topY = static_cast<int>(newY) / TILE_SIZE;
    int bottomY = static_cast<int>(newY + pmRect.h - 1) / TILE_SIZE;

    // ??m b?o các ch? s? n?m trong gi?i h?n c?a b?n ?? b?ng cách s? d?ng wrap around
    leftX = (leftX + map[0].size()) % map[0].size();
    rightX = (rightX + map[0].size()) % map[0].size();
    topY = (topY + map.size()) % map.size();
    bottomY = (bottomY + map.size()) % map.size();

    // Ki?m tra va ch?m v?i các b?c t??ng
    return !(map[topY][leftX] == 1 || map[topY][rightX] == 1 || map[bottomY][leftX] == 1 || map[bottomY][rightX] == 1);
}

void Pacman::render(SDL_Renderer* rd) {
	SDL_SetRenderDrawColor(rd, 255, 255, 0, 255);
	SDL_RenderFillRect(rd, &pmRect);
}

float Pacman::getPosX() {
	return posX;
}

float Pacman::getPosY() {
	return posY;
}