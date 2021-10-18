
#define SDL_MAIN_HANDLED

#include <iostream>
#include <math.h>
#include "window.hpp"

void SDL_FillCircle(SDL_Surface *surface, int x, int y, float radius, Uint32 color){
	for(int i = 0; i < radius; i++){
		for(int j = 0; j < radius; j++){
			if( i * i + j * j <= radius * radius ){
				SDL_DrawPixel(surface, x + i, y + j, color);
				SDL_DrawPixel(surface, x - i, y + j, color);
				SDL_DrawPixel(surface, x + i, y - j, color);
				SDL_DrawPixel(surface, x - i, y - j, color);
			}
		}
	}
}

int sign (int x1, int y1, int x2, int y2, int x3, int y3) 
{
    return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}

bool PointInTriangle (int px, int py, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(px, py, x1, y1, x2, y2);
    d2 = sign(px, py, x2, y2, x3, y3);
    d3 = sign(px, py, x3, y3, x1, y1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void SDL_FillTriangle(SDL_Surface *surface, int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color){
	int minx = x1 < x2 ? x1 : x2;
	minx = minx < x3 ? minx : x3;

	int maxx = x1 > x2 ? x1 : x2;
	maxx = maxx > x3 ? maxx : x3;

	int miny = y1 < y2 ? y1 : y2;
	miny = miny < y3 ? miny : y3;

	int maxy = y1 > y2 ? y1 : y2;
	maxy = maxy > y3 ? maxy : y3;

	for (int i = miny; i < maxy; i++)
	{
		for(int j = minx; j < maxx; j++)\
		{
			if(PointInTriangle(j, i, x1, y1, x2, y2, x3, y3)){
				SDL_DrawPixel(surface, j, i, color);
			}
		}
	}
	
}



int main(int argc, char *argv[]) {
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL " << SDL_GetError() << std::endl;
		return -1;
	}


	{
		Window window("Psychic Guacamole", 500, 500);

		// While SDL doesn't want to quit
		bool shouldQuit = false;
		SDL_Event event;
		while(!shouldQuit) {
			if(SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT) shouldQuit = true;
			}

			// Draw a red rectangle to the screen
			SDL_Rect rect = { 50, 50, 100, 100 };
			SDL_Surface *surface = window.Surface();
			SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
			SDL_FillCircle(surface, 400, 400, 50, SDL_MapRGBA(surface->format, 0, 0, 255, 255));
			
			SDL_FillTriangle(surface, 160, 200, 210, 400, 340, 300, SDL_MapRGBA(surface->format, 255, 255, 0, 255));
			SDL_FillTriangle2(surface, { 20, 100 }, { 50, 30 }, { 230, 40 }, SDL_MapRGBA(surface->format, 255, 255, 255, 255));

			window.Update();
		}
	}
	
	SDL_Quit();
	return 0;
}