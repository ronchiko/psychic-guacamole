
#define SDL_MAIN_HANDLED

#include <iostream>
#include "window.hpp"


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
			SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, 0, 0, 0, 255));
			
			SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
			SDL_FillCircle(surface, 400, 400, 50, SDL_MapRGBA(surface->format, 0, 0, 255, 255));
			SDL_FillCircle(surface, 400, 350, 50, SDL_MapRGBA(surface->format, 255, 0, 255, 255));
			
			SDL_FillTriangle(surface, {60, 100}, {110, 300}, {240, 400}, SDL_MapRGBA(surface->format, 255, 255, 0, 255));			
			SDL_FillTriangleAntiAliasing(surface, {260.0f, 100.0f}, {310.0f, 300.0f}, {440.0f, 400.0f}, SDL_MapRGBA(surface->format, 255, 255, 0, 255));
			SDL_FillTriangle2(surface, { 20, 100 }, { 50, 30 }, { 230, 40 }, SDL_MapRGBA(surface->format, 255, 255, 255, 255));
			Point2d polygon[5] = { { 50, 50 }, { 100, 30 }, { 260, 170 }, { 490, 350 }, { 330, 460 } };
			//SDL_FillPoly(surface, polygon, 5, SDL_MapRGBA(surface->format, 0, 255, 255, 255));

			window.Update();
		}
	}
	
	SDL_Quit();
	return 0;
}