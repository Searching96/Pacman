#include "Ghost.h"

Ghost::Ghost(int _x, int _y, int _w, int _h, float _speed)
	: speed(_speed), dirX(0), dirY(0), posX(_x), posY(_y), tempDirX(0), tempDirY(0) {
	ghostRect = { _x, _y, _w, _h };
}

bool Ghost::isValidMove(float newX, float newY, const vector<vector<int>>& map) {
    // Tính toán các ch? s? c?a các ?i?m xung quanh Pacman
    int leftX = static_cast<int>(newX) / TILE_SIZE;
    int rightX = static_cast<int>(newX + ghostRect.w - 1) / TILE_SIZE;
    int topY = static_cast<int>(newY) / TILE_SIZE;
    int bottomY = static_cast<int>(newY + ghostRect.h - 1) / TILE_SIZE;

    // ??m b?o các ch? s? n?m trong gi?i h?n c?a b?n ?? b?ng cách s? d?ng wrap around
    leftX = (leftX + map[0].size()) % map[0].size();
    rightX = (rightX + map[0].size()) % map[0].size();
    topY = (topY + map.size()) % map.size();
    bottomY = (bottomY + map.size()) % map.size();

    // Ki?m tra va ch?m v?i các b?c t??ng
    return !(map[topY][leftX] == 1 || map[topY][rightX] == 1 || map[bottomY][leftX] == 1 || map[bottomY][rightX] == 1);
}

void Ghost::randomMove(const vector<vector<int>>& map) {
    vector<pair<int, int>> possibleMoves;

    // Ki?m tra các h??ng có th? di chuy?n và thêm vào danh sách
    if (isValidMove(posX, posY - speed, map)) {
        possibleMoves.push_back(make_pair(0, -1)); // Lên
    }
    if (isValidMove(posX, posY + speed, map)) {
        possibleMoves.push_back(make_pair(0, 1)); // Xu?ng
    }
    if (isValidMove(posX - speed, posY, map)) {
        possibleMoves.push_back(make_pair(-1, 0)); // Trái
    }
    if (isValidMove(posX + speed, posY, map)) {
        possibleMoves.push_back(make_pair(1, 0)); // Ph?i
    }

    if (!possibleMoves.empty()) {
        srand(time(0));
        int randomIndex = rand() % possibleMoves.size();
        dirX = possibleMoves[randomIndex].first;
        dirY = possibleMoves[randomIndex].second;
    }
}

void Ghost::chasePacman(Pacman* pacman, const vector<vector<int>>& map) {
    // Calculate distances in each direction
    float distUp = calculateDistance(posX, posY - speed, pacman->getPosX(), pacman->getPosY());
    float distDown = calculateDistance(posX, posY + speed, pacman->getPosX(), pacman->getPosY());
    float distLeft = calculateDistance(posX - speed, posY, pacman->getPosX(), pacman->getPosY());
    float distRight = calculateDistance(posX + speed, posY, pacman->getPosX(), pacman->getPosY());

    // Determine valid directions
    vector<pair<int, float>> directions;

    if (isValidMove(posX, posY - speed, map)) {
        directions.push_back({ 0, distUp });
    }
    if (isValidMove(posX, posY + speed, map)) {
        directions.push_back({ 1, distDown });
    }
    if (isValidMove(posX - speed, posY, map)) {
        directions.push_back({ 2, distLeft });
    }
    if (isValidMove(posX + speed, posY, map)) {
        directions.push_back({ 3, distRight });
    }

    // Choose a random valid direction
    if (!directions.empty()) {
        srand(static_cast<unsigned int>(time(0)));
        int randomIndex = rand() % directions.size();
        switch (directions[randomIndex].first) {
        case 0: // Up
            dirX = 0;
            dirY = -1;
            break;
        case 1: // Down
            dirX = 0;
            dirY = 1;
            break;
        case 2: // Left
            dirX = -1;
            dirY = 0;
            break;
        case 3: // Right
            dirX = 1;
            dirY = 0;
            break;
        }
    }
    else {
        // No valid direction to chase, move randomly
        randomMove(map);
    }

    // Move ghost
    posX += dirX * speed;
    posY += dirY * speed;

    // Wrap around logic
    wrapAround();

    // Update rect position
    ghostRect.x = static_cast<int>(posX);
    ghostRect.y = static_cast<int>(posY);
}

void Ghost::wrapAround() {
    if (posX < 0) posX = MAP_WIDTH - 1;
    if (posX >= MAP_WIDTH) posX = 0;
    if (posY < 0) posY = MAP_HEIGHT - 1;
    if (posY >= MAP_HEIGHT) posY = 0;
}

float Ghost::calculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Ghost::render(SDL_Renderer* rd) {
	SDL_SetRenderDrawColor(rd, 0x00, 0xFF, 0x00, 0xFF); // Red ghost
	SDL_RenderFillRect(rd, &ghostRect);
}