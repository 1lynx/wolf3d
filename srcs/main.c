#include "SDL2/SDL.h"
#include <stdio.h>

# define XSZ 1000
# define YSZ 1000

int main(int ac, char **av)
{
    SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	*av = NULL;
	ac = 0;
	int i = 0;

    SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        0,           // initial x position
        0,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	while (!i)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			i = 1;
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
 		SDL_RenderPresent(renderer);
	}

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
