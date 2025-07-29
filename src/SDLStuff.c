#include "SDLStuff.h"

void initSDL(SDLInfo* info)
{
	memset(info, 0, sizeof(SDLInfo));

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	info->window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!info->window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	info->renderer = SDL_CreateRenderer(info->window, -1, SDL_RENDERER_ACCELERATED);

	if (!info->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_RenderSetLogicalSize(info->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderSetIntegerScale(info->renderer, 1);
	
	info->surface = SDL_GetWindowSurface(info->window);
}


void flipBuffer()
{
	SDL_RenderPresent(sdlInfo.renderer);
}