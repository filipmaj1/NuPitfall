#pragma once

#include <SDL.h>

#define SCREEN_WIDTH   (640 * 2)
#define SCREEN_HEIGHT  (480 * 2)

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* surface;
} SDLInfo;

SDLInfo sdlInfo;