
#pragma once

#include <cstdio>
#include <SDL.h>

struct Point2d {
	int x, y;
};
typedef Uint32 Color;

#define SDL_DrawPixel(surface, x, y, color) (((Uint32*)(surface) -> pixels)[((y) * (surface) -> w + (x))] = (color))

/** \brief This method blends 2 pixels of a surface using a blend factor */
inline void SDL_BlendPixel(SDL_Surface *surface, int x, int y, Color c, float blend) {
	Color out = 0;
	Color *at = (Color *)surface->pixels + y * surface->w + x;

	// Each pixel has 4 components of 1 byte, the size of each pixel is 4 bytes
	// Here we blend each of those components into out 
	for(int i = 0; i < sizeof(Color) * 8; i += sizeof(unsigned char) * 8) {
		unsigned char _blend_from 	= *at >> i;
		unsigned char _blend_in 	= c >> i;
		float _blend = _blend_in * blend + _blend_from * (1 - blend);
		out |= (unsigned char)_blend << i;
	}
	*at = out;
}

void SDL_DrawHLine(SDL_Surface *surface, int x1, int x2, int y, Color color);
void SDL_FillTriangle(SDL_Surface *surface, int x1, int y1, int x2, int y2, int x3, int y3, Color color);
void SDL_FillTriangle2(SDL_Surface *surface, const Point2d&, const Point2d&, const Point2d&, Color);
void SDL_FillCircle(SDL_Surface *surface, int x, int y, float radius, Color color);

void SDL_FillPoly(SDL_Surface *s, const Point2d *p, size_t len, Color c);