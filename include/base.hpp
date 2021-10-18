
#pragma once

#include <cstdio>
#include <SDL.h>

struct Point2d {
	int x, y;
};
typedef Uint32 Color;

#define SDL_DrawPixel(surface, x, y, color) (((Uint32*)(surface) -> pixels)[((y) * (surface) -> w + (x))] = (color))

void SDL_DrawHLine(SDL_Surface *surface, int x1, int x2, int y, Color color);
void SDL_FillTriangle(SDL_Surface *surface, int x1, int y1, int x2, int y2, int x3, int y3, Color color);
void SDL_FillTriangle2(SDL_Surface *surface, const Point2d&, const Point2d&, const Point2d&, Color);
void SDL_FillCircle(SDL_Surface *surface, int x, int y, float radius, Color color);