#include "Map.h"

Map::Map() {
	tileRect.w = TILE_SIZE;
	tileRect.h = TILE_SIZE;
}

void Map::loadMap(const vector<vector<int>>& _map) {
	map = _map;
}

void Map::render(SDL_Renderer* rd) {
	for (int row = 0; row < map.size(); row++)
		for (int col = 0; col < map[row].size(); col++)
			drawTile(rd, col * TILE_SIZE, row * TILE_SIZE, map[row][col]);
}

void Map::drawTile(SDL_Renderer* rd, int x, int y, int type) {
	tileRect.x = x;
	tileRect.y = y;

	switch (type) {
	case 0:
		SDL_SetRenderDrawColor(rd, 0xFF, 0xFF, 0xFF, 0xFF); // empty space
		break;
	case 1:
		SDL_SetRenderDrawColor(rd, 0x00, 0x00, 0xFF, 0xFF); // wall
		break;
	default:
		SDL_SetRenderDrawColor(rd, 0xFF, 0xFF, 0xFF, 0xFF);
		break;
	}

	SDL_RenderFillRect(rd, &tileRect);
	SDL_SetRenderDrawColor(rd, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(rd, &tileRect);
}

vector<vector<int>> Map::getMap() {
	return map;
}