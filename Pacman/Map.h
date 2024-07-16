#pragma once
#include <SDL.h>
#include <vector>
#include "Const.h"

using namespace std;

class Map
{
private:
	vector<vector<int>> map;
	SDL_Rect tileRect;

	void drawTile(SDL_Renderer* rd, int x, int y, int type);
public:
	Map();
	void loadMap(const vector<vector<int>>& _map);
	void render(SDL_Renderer* rd);
	vector<vector<int>> getMap();
};

