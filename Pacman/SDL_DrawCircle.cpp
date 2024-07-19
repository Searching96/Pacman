#include "SDL_DrawCircle.h"

void drawPoint(SDL_Renderer* rd, int x, int y) {
    SDL_RenderDrawPoint(rd, x, y);
}

void SDL_RenderDrawCircle(SDL_Renderer* rd, float centerX, float centerY, int radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        // 8-way symmetry
        drawPoint(rd, static_cast<int>(centerX) + x, static_cast<int>(centerY) - y);
        drawPoint(rd, static_cast<int>(centerX) - x, static_cast<int>(centerY) - y);
        drawPoint(rd, static_cast<int>(centerX) - x, static_cast<int>(centerY) + y);
        drawPoint(rd, static_cast<int>(centerX) + y, static_cast<int>(centerY) - x);
        drawPoint(rd, static_cast<int>(centerX) + x, static_cast<int>(centerY) + y);
        drawPoint(rd, static_cast<int>(centerX) + y, static_cast<int>(centerY) + x);
        drawPoint(rd, static_cast<int>(centerX) - y, static_cast<int>(centerY) - x);
        drawPoint(rd, static_cast<int>(centerX) - y, static_cast<int>(centerY) + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void SDL_RenderDrawFilledCircle(SDL_Renderer* rd, float x, float y, int radius, SDL_Color color) {
    SDL_SetRenderDrawBlendMode(rd, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rd, color.r, color.g, color.b, color.a);

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(rd, x + dx, y + dy);
            }
        }
    }
}