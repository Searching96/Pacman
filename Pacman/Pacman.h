#pragma once
#include <SDL.h>
#include <vector>
#include "Const.h"

using namespace std;

class Pacman {
private:
	SDL_Rect pmRect;
	float speed;
	int dirX, dirY;
	float posX, posY;
public:
	Pacman(int _x, int _y, int _w, int _h, float _speed);
	void handleEvent(SDL_Event& ev);
	void move(const vector<vector<int>>& map);
	void render(SDL_Renderer* rd);
	bool isValidMove(float newX, float newY, const vector<vector<int>>& map);
};