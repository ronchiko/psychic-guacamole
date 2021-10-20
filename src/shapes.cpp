
#include <SDL.h>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include<iostream>

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

void SDL_FillPoly(SDL_Surface *s, const Point2d *p, size_t len, Color c) {
	for(int i = 0; i < len - 2; ++i) {
		SDL_FillTriangle2(s, p[i], p[i + 1], p[i + 2], c);
	}
}

float signf (Pointf2d p1, Pointf2d p2, Pointf2d p3) 
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int sign (Point2d p1, Point2d p2, Point2d p3){
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (Point2d p, Point2d v1, Point2d v2, Point2d v3)
{
    int d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(p, v1, v2);
    d2 = sign(p, v2, v3);
    d3 = sign(p, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    //return !(has_neg && has_pos);
	return has_neg ^ has_pos;
}

bool PointInTriangle (Pointf2d p, Pointf2d v1, Pointf2d v2, Pointf2d v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = signf(p, v1, v2);
    d2 = signf(p, v2, v3);
    d3 = signf(p, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    //return !(has_neg && has_pos);
	return has_neg ^ has_pos;
}

void SDL_FillTriangle(SDL_Surface *surface, Point2d p1, Point2d p2, Point2d p3, Color color){
	int xs[3] = {p1.x, p2.x, p3.x};
	auto mmx = std::minmax_element(xs, xs + 3);

	int ys[3] = {p1.y, p2.y, p3.y};
	auto mmy = std::minmax_element(ys, ys + 3);

	for (int i = *mmy.first; i < *mmy.second; i++)
	{
		for(int j = *mmx.first; j < *mmx.second; j++)
		{
			if(PointInTriangle({j, i}, p1, p2, p3)){
				SDL_DrawPixel(surface, j, i, color);
			}
		}
	}
}

void SDL_FillTriangleAntiAliasing(SDL_Surface *surface, Pointf2d p1, Pointf2d p2, Pointf2d p3, Color color){
	constexpr static float BLEND_FACTOR = 10;
	float xs[3] = {p1.x, p2.x, p3.x};
	auto mmx = std::minmax_element(xs, xs + 3);

	float ys[3] = {p1.y, p2.y, p3.y};
	auto mmy = std::minmax_element(ys, ys + 3);

	for (float i = *mmy.first; i < *mmy.second; i++)
	{
		for(float j = *mmx.first; j < *mmx.second; j++)
		{
			if(PointInTriangle({j, i}, p1, p2, p3)){
				int N = 1000;
				float sum = 0;
				for(int k = 0; k < N; k++)
				{
					float minx = j * 1000 - 500;
					float maxx = j * 1000 + 500;

					float miny = i * 1000 - 500;
					float maxy = i  * 1000 + 500;

					int ran = std::rand();
					int range = maxx - minx + 1;
					float x = ( (float)(ran % range) + minx ) / 1000.0f;

					ran = std::rand();
					range = maxy - miny + 1;
					float y = ( (float)(ran % range) + miny ) / 1000.0f;

					//std::cout << j << " " << i << " , " <<  x << " " << y << std::endl;
					

					if(PointInTriangle({x, y}, p1, p2, p3))
					{
						++sum;
					}
				}

				float coverage = sum / (float) N;
				//std::cout << coverage << std::endl;
				SDL_BlendPixel(surface, j, i, color, coverage);
			}
		}
	}
	
}

void SDL_FillCircle(SDL_Surface *surface, int x, int y, float radius, Color color){
	constexpr static float BLEND_FACTOR = 10;		// Greater then 0 

	for(int i = 0; i < radius; i++){
		for(int j = 0; j < radius; j++){

			float ratio = (i * i + j * j) / (radius * radius);
			if(ratio <= 1){
				// b = 1 - r ^ BLEND
				float blend = 1 - (float)std::pow(ratio, BLEND_FACTOR);
				
				SDL_BlendPixel(surface, x + i, y + j, color, blend);
				SDL_BlendPixel(surface, x - i, y - j, color, blend);
				// To avoid drawing over a drawn pixel this check is nessecary
				if(i != 0 && j != 0 && j != radius && i != radius) {
					SDL_BlendPixel(surface, x - i, y + j, color, blend);
					SDL_BlendPixel(surface, x + i, y - j, color, blend);
				}
			}
		}
	}
}
