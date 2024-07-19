#pragma once
#include <SDL.h>
#include <vector>
#include "Const.h"
#include "Pellet.h"

using namespace std;

class Pacman {
private:
	SDL_Rect pmRect;
	float speed;
	int dirX, dirY;
	float posX, posY;
	int tempDirX, tempDirY;
public:
	Pacman(int _x, int _y, int _w, int _h, float _speed);
	void handleEvent(SDL_Event& ev);
	void move(const vector<vector<int>>& map, vector<Pellet>& pellets);
	void render(SDL_Renderer* rd);
	bool isValidMove(float newX, float newY, const vector<vector<int>>& map);
	void wrapAround(float& x, float& y);
	float getPosX();
	float getPosY();
	void checkPelletCollision(vector<Pellet>& pellets);
	SDL_Rect getRect();
};