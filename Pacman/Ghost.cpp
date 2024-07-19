#include "Ghost.h"

Ghost::Ghost(int _x, int _y, int _w, int _h, float _speed, float _chaseDistance, char _color)
    : speed(_speed), dirX(0), dirY(0), posX(static_cast<float>(_x)), posY(static_cast<float>(_y)),
      tempDirX(0), tempDirY(0), chaseDistance(_chaseDistance), color(_color) {
    ghostRect = { _x, _y, _w, _h };
}

bool Ghost::isValidMove(float newX, float newY, const vector<vector<int>>& map) {
    if (newX < 0 || newX + ghostRect.w > MAP_WIDTH || newY < 0 || newY + ghostRect.h > MAP_HEIGHT)
        return false;
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
        srand(static_cast<unsigned int>(time(0)));
        int randomIndex = rand() % possibleMoves.size();
        dirX = possibleMoves[randomIndex].first;
        dirY = possibleMoves[randomIndex].second;
    }
}

void Ghost::chasePacman(Pacman* pacman, const vector<vector<int>>& map) {
    float distUp = calculateDistance(posX, posY - speed, pacman->getPosX(), pacman->getPosY());
    float distDown = calculateDistance(posX, posY + speed, pacman->getPosX(), pacman->getPosY());
    float distLeft = calculateDistance(posX - speed, posY, pacman->getPosX(), pacman->getPosY());
    float distRight = calculateDistance(posX + speed, posY, pacman->getPosX(), pacman->getPosY());

    // if there is a direction to chase
    if (distUp < chaseDistance || distDown < chaseDistance || distLeft < chaseDistance || distRight < chaseDistance) {
        if (distUp <= distDown && distUp <= distLeft && distUp <= distRight) {
            dirX = 0;
            dirY = -1; // chase up
        }
        else if (distDown <= distUp && distDown <= distLeft && distDown <= distRight) {
            dirX = 0;
            dirY = 1; // chase down
        }
        else if (distLeft <= distUp && distLeft <= distDown && distLeft <= distRight) {
            dirX = -1;
            dirY = 0; // chase left
        }
        else {
            dirX = 1;
            dirY = 0; // chase right
        }
    }
    // no direction to chase
    else {
        randomMove(map);
    }

    // move ghost
    posX += dirX * speed;
    posY += dirY * speed;

    wrapAround();

    // update rect
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
    return static_cast<float>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void Ghost::render(SDL_Renderer* rd) {
    SDL_Color ghostColor;
    switch (color)
    {
    case 'R':
        ghostColor = { 255, 0, 0, 255 };
        break;
    case 'P':
        ghostColor = { 255, 192, 203, 255 };
        break;
    case 'C':
        ghostColor = { 0, 255, 255, 255 };
        break;
    case 'O':
        ghostColor = { 255, 165, 0, 255 };
        break;
    default:
        break;
    }
    SDL_SetRenderDrawColor(rd, ghostColor.r, ghostColor.g, ghostColor.b, ghostColor.a);
    SDL_RenderFillRect(rd, &ghostRect);
    drawChaseDistance(rd);
}

void Ghost::drawChaseDistance(SDL_Renderer* rd) {
    int centerX = static_cast<int>(posX) + ghostRect.w / 2;
    int centerY = static_cast<int>(posY) + ghostRect.h / 2;
    SDL_SetRenderDrawColor(rd, 255, 0, 0, 255); // Màu ?? cho vòng tròn
    SDL_RenderDrawCircle(rd, static_cast<float>(centerX), static_cast<float>(centerY), static_cast<int>(chaseDistance));
}

SDL_Rect Ghost::getRect() {
    return ghostRect;
}

bool Ghost::checkPacmanCollision(Pacman* pacman) {
    SDL_Rect pacmanRect = pacman->getRect();
    return (SDL_HasIntersection(&ghostRect, &pacmanRect));
}