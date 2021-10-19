#pragma once

#include <SDL.h>

#include "base.hpp"

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