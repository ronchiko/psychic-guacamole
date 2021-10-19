
#include <SDL.h>
#include <cstdio>
#include <algorithm>

#include "base.hpp"

void SDL_DrawHLine(SDL_Surface *surface, int x1, int x2, int y, Color color) {
	auto mnx = std::minmax(x1, x2);
	
	auto begin = std::max(0, mnx.first), end = std::min(mnx.second, surface->w);
	for(int x = begin; x < end; ++x) 
		SDL_DrawPixel(surface, x, y, color);
} 

void SDL_FillTriangle2(SDL_Surface *surface, const Point2d& a, const Point2d& b, const Point2d& c, Color cl) {
	// Another method to draw a triangle
	Point2d sorted[3] = { a, b, c };
	std::sort(sorted, sorted + 3, [](const Point2d& x, const Point2d& y) { return y.y > x.y; } );

	const float deltas[3] = { 
		(float)(sorted[0].x - sorted[1].x) / (sorted[0].y - sorted[1].y), 
		(float)(sorted[0].x - sorted[2].x) / (sorted[0].y - sorted[2].y),
		(float)(sorted[1].x - sorted[2].x) / (sorted[1].y - sorted[2].y)
	};
	float x0 = sorted[0].x, x1 = x0; 

	for(int p = 0; p <= 1; ++p, std::swap(x1, x0)) {
		for(int i = sorted[p].y; i < sorted[p + 1].y; ++i, x0 += deltas[p], x1 += deltas[p + 1]) 
			SDL_DrawHLine(surface, x0, x1, i, cl);
	}
}