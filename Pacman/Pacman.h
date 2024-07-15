#pragma once

#include <SDL.h>

class Pacman {
private:
	int x, y;
	int w, h;
	int speed;
public:
	Pacman(int _x, int _y, int _w, int _h, int _speed);
	void move(SDL_Event& ev);
	void render(SDL_Renderer* rd);
};