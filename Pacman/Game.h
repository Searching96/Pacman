#pragma once
#include <SDL.h>
#include "Pacman.h"
#include "Ghost.h"
#include "Map.h"
#include "Const.h"

class Game {
private:
	SDL_Window* wd;
	SDL_Renderer* rd;
	bool quit;
	Pacman* pm;
	vector<Ghost*> ghosts;
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

