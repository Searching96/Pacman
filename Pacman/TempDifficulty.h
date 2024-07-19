#pragma once
// ghost xuyen tuong
//bool Ghost::isValidMove(float newX, float newY, const vector<vector<int>>& map) {
//    if (newX < 0 || newX + ghostRect.w > MAP_WIDTH || newY < 0 || newY + ghostRect.h > MAP_HEIGHT)
//        return false;
//}

// ghost chon huong ngan nhat (chi tot khi co the xuyen tuong)
//void Ghost::chasePacman(Pacman* pacman, const vector<vector<int>>& map) {
//    // Calculate distances in each direction
//    float distUp = calculateDistance(posX, posY - speed, pacman->getPosX(), pacman->getPosY());
//    float distDown = calculateDistance(posX, posY + speed, pacman->getPosX(), pacman->getPosY());
//    float distLeft = calculateDistance(posX - speed, posY, pacman->getPosX(), pacman->getPosY());
//    float distRight = calculateDistance(posX + speed, posY, pacman->getPosX(), pacman->getPosY());
//
//    // Determine valid directions
//    vector<pair<int, float>> directions;
//
//    if (isValidMove(posX, posY - speed, map)) {
//        directions.push_back({ 0, distUp });
//    }
//    if (isValidMove(posX, posY + speed, map)) {
//        directions.push_back({ 1, distDown });
//    }
//    if (isValidMove(posX - speed, posY, map)) {
//        directions.push_back({ 2, distLeft });
//    }
//    if (isValidMove(posX + speed, posY, map)) {
//        directions.push_back({ 3, distRight });
//    }
//
//    // Sort directions by distance (ascending)
//    sort(directions.begin(), directions.end(), [](const pair<int, float>& a, const pair<int, float>& b) {
//        return a.second < b.second;
//        });
//
//    // Choose the best valid direction
//    if (!directions.empty()) {
//        switch (directions[0].first) {
//        case 0: // Up
//            dirX = 0;
//            dirY = -1;
//            break;
//        case 1: // Down
//            dirX = 0;
//            dirY = 1;
//            break;
//        case 2: // Left
//            dirX = -1;
//            dirY = 0;
//            break;
//        case 3: // Right
//            dirX = 1;
//            dirY = 0;
//            break;
//        }
//    }
//    else {
//        // No valid direction to chase, move randomly
//        randomMove(map);
//    }
//
//    // Move ghost
//    posX += dirX * speed;
//    posY += dirY * speed;
//
//    // Wrap around logic
//    wrapAround();
//
//    // Update rect position
//    ghostRect.x = static_cast<int>(posX);
//    ghostRect.y = static_cast<int>(posY);
//}
