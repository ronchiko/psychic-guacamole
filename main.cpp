
#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL/SDL.h>

int main(int argc, char *argv[]) {
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create a window
	SDL_Window *window = SDL_CreateWindow("Psychic Guacamole", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);
	SDL_Surface *surface = SDL_GetWindowSurface(window);

	// While SDL doesn't want to quit
	bool shouldQuit = false;
	SDL_Event event;
	while(!shouldQuit) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) shouldQuit = true;
		}

		// Draw a rectangle to the screen
		SDL_Rect rect = { 50, 50, 100, 100 };
		SDL_FillRect(surface, &rect, 0xFF0000FF);

		SDL_UpdateWindowSurface(window);
	}

	// Cleanup SDL
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}