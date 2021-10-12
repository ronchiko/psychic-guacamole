#pragma once

#include <SDL.h>

void SDL_FillCircle(SDL_Surface *surface, int x, int y, float radius, Uint32 color);

class Window {
public:
	Window(const char *title, int w, int h);
	~Window();
	
    void Update();
	
	inline SDL_Surface *Surface() noexcept { return surface; }
	inline const SDL_Surface *Surface() const noexcept { return surface; }
private:
    SDL_Window *window;
    SDL_Surface *surface;
};