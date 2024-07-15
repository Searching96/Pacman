#pragma once
#include <SDL.h>
#include "Pacman.h"
#include "Map.h"

class Game {
private:
	SDL_Window* wd;
	SDL_Renderer* rd;
	bool quit;
	Pacman* pm;
	Map* map;

	void handleEvents();
	void update();
	void render();
public:
	Game();
	bool init();
	void run();
	void close();
};

