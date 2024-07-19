#pragma once
#include <SDL.h>
#include <vector>
#include <random>
#include "Const.h"
#include "Djikstra.h"
#include "Pacman.h"
#include "SDL_DrawCircle.h"

using namespace std;

class Ghost
{
private:
	SDL_Rect ghostRect;
	float speed;
	int dirX, dirY;
	float posX, posY;
	int tempDirX, tempDirY;
	float chaseDistance;
	char color;
public:
	Ghost(int _x, int _y, int _w, int _h, float _speed, float _chaseDistance, char _color);
	void chasePacman(Pacman* pacman, const vector<vector<int>>& map);
	void render(SDL_Renderer* rd);
	bool isValidMove(float newX, float newY, const vector<vector<int>>& map);
	float calculateDistance(float x1, float y1, float x2, float y2);
	void randomMove(const vector<vector<int>>& map);
	void wrapAround();
	void drawChaseDistance(SDL_Renderer* rd);
	SDL_Rect getRect();
	bool checkPacmanCollision(Pacman* pacman);
};
