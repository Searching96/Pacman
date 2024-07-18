#include "Game.h"
#include "Const.h"
#include <iostream>
using namespace std;

Game::Game() : wd(NULL), rd(NULL), quit(false), pm(NULL), map(NULL) {}

bool Game::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	
	wd = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAP_WIDTH, MAP_HEIGHT, SDL_WINDOW_SHOWN);
	if (wd == NULL) {
		cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	rd = SDL_CreateRenderer(wd, -1, SDL_RENDERER_ACCELERATED);
	if (rd == NULL) {
		cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	const float SPEED = 0.050f;
	pm = new Pacman(20, 20, 20, 20, SPEED);
	ghosts.push_back(new Ghost(20, 60, 20, 20, 0.35f * SPEED));
	ghosts.push_back(new Ghost(80, 20, 20, 20, 0.30f * SPEED));
	ghosts.push_back(new Ghost(100, 100, 20, 20, 0.25f * SPEED));
	ghosts.push_back(new Ghost(200, 200, 20, 20, 0.20f * SPEED));
	map = new Map();
	map->loadMap(MAP);
	return true;
}

void Game::run() {
	while (!quit) {
		handleEvents();
		update();
		render();
	}
}

void Game::close() {
	delete pm;
	delete map;
	for (auto ghost : ghosts)
		delete ghost;
	SDL_DestroyRenderer(rd);
	SDL_DestroyWindow(wd);
	SDL_Quit();
}

void Game::handleEvents() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0) {
		if (ev.type == SDL_QUIT) {
			quit = true;
		}
		pm->handleEvent(ev);
	}
}

void Game::update() {
	pm->move(map->getMap());
	for (auto ghost : ghosts)
		ghost->chasePacman(pm, map->getMap());
}

void Game::render() {
	SDL_SetRenderDrawColor(rd, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(rd);
	map->render(rd);
	pm->render(rd);
	for (auto ghost : ghosts)
		ghost->render(rd);
	SDL_RenderPresent(rd);
}