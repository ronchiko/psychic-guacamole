
#define SDL_MAIN_HANDLED

#include <iostream>
#include "window.hpp"

#define SDL_DrawPixel(surface, x, y, color) (((Uint32*)(surface) -> pixels)[((y) * (surface) -> w + (x))] = (color))

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
			SDL_FillCircle(surface, 400, 400, 50, SDL_MapRGBA(surface->format, 255, 0, 255, 255));
			
			window.Update();
		}
	}
	
	SDL_Quit();
	return 0;
}