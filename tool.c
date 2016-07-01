#include "header/wolf.h"

int set_up(t_info *e)
{
	SDL_Init(SDL_INIT_VIDEO);

	e->win = SDL_CreateWindow("Ray", 0, 0, XSZ, YSZ, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (e->win == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return(0);
	}
	e->rend = SDL_CreateRenderer(e->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return(0);
}

void 	set_up_value(t_info *e)
{
	e->posX = 22;
	e->posY = 12;
	e->dirX = -1;
	e->dirY = 0;
	e->planeX = 0;
	e->planeY = 0.66;
	e->newtime = 0;
	e->oldtime = 0;
}

void re_calc(t_info *e)
{
	e->cameraX = 2 * e->x / (double)XSZ - 1;
	e->rayPosX = e->posX;
	e->rayPosY = e->posY;
	e->rayDirX = e->dirX + e->planeX * e->cameraX;
	e->rayDirY = e->dirY + e->planeY * e->cameraX;
	e->mapX = e->rayPosX;
	e->mapY = e->rayPosY;
	e->deltaDistX = sqrt(1 + (e->rayDirY * e->rayDirY) / (e->rayDirX * e->rayDirX));
	e->deltaDistY = sqrt(1 + (e->rayDirX * e->rayDirX) / (e->rayDirY * e->rayDirY));
	e->hit = 0;
}

void line_color(t_info *e)
{
  SDL_SetRenderDrawColor(e->rend, 66, 66, 66, 255);
	SDL_RenderDrawLine(e->rend, e->x, e->drawStart, e->x, e->drawEnd);
  SDL_SetRenderDrawColor(e->rend, 51, 204, 255, 255);
	SDL_RenderDrawLine(e->rend, e->x, e->drawStart, e->x, 0);
  SDL_SetRenderDrawColor(e->rend, 255, 255, 255, 255);
	SDL_RenderDrawLine(e->rend, e->x, e->drawEnd, e->x, YSZ);
}
