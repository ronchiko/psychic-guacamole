
#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL/SDL.h>

int main(int argc, char *argv[]) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("Psychic Guacamole", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);
	SDL_Surface *surface = SDL_GetWindowSurface(window);

	bool shouldQuit = false;
	SDL_Event event;
	while(!shouldQuit) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) shouldQuit = true;
		}

		SDL_UpdateWindowSurface(window);
	}

	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}