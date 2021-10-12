#include "window.hpp"

Window::Window(const char *title, int w, int h): window(nullptr), surface(nullptr) {
    // Create a window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0); 
    surface = SDL_GetWindowSurface(window);
}

Window::~Window() {
    SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
}

void Window::Update() {
    SDL_UpdateWindowSurface(window);
}