#include "../header/wolf.h"

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

void init(t_info *e)
{
	e->cameraX = 2 * e->x / (double)YSZ - 1;
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
	SDL_SetRenderDrawColor(e->rend, 0, 0, 0, 255);
	SDL_RenderDrawLine(e->rend, e->x, e->drawStart, e->x, e->drawEnd);
	SDL_SetRenderDrawColor(e->rend, 255, 255, 255, 255);
	SDL_RenderDrawLine(e->rend, e->x, e->drawStart, e->x, 0);
	SDL_SetRenderDrawColor(e->rend, 160, 160, 160, 255);
	SDL_RenderDrawLine(e->rend, e->x, e->drawEnd, e->x, YSZ);
}

void calcul(t_info *e, int worldMap[mapWidth][mapHeight])
{
	e->x = 0;
	while(e->x < XSZ)
	{
		init(e);
		if (e->rayDirX < 0)
		{
			e->stepX = -1;
			e->sideDistX = (e->rayPosX - e->mapX) * e->deltaDistX;
		}
		else
		{
			e->stepX = 1;
			e->sideDistX = (e->mapX + 1.0 - e->rayPosX) * e->deltaDistX;
		}
		if (e->rayDirY < 0)
		{
			e->stepY = -1;
			e->sideDistY = (e->rayPosY - e->mapY) * e->deltaDistY;
		}
		else
		{
			e->stepY = 1;
			e->sideDistY = (e->mapY + 1.0 - e->rayPosY) * e->deltaDistY;
		}

		while (e->hit == 0)
		{
  			if (e->sideDistX < e->sideDistY)
  			{
				e->sideDistX += e->deltaDistX;
				e->mapX += e->stepX;
				e->side = 0;
  			}
  			else
  			{
				e->sideDistY += e->deltaDistY;
				e->mapY += e->stepY;
				e->side = 1;
  			}
  			if (worldMap[e->mapX][e->mapY] > 0)
				e->hit = 1;
		}

		if (e->side == 0)
			e->perpWallDist = (e->mapX - e->rayPosX + (1 - e->stepX) / 2) / e->rayDirX;
		else
			e->perpWallDist = (e->mapY - e->rayPosY + (1 - e->stepY) / 2) / e->rayDirY;

		printf("side : %f\n", e->perpWallDist);

		e->lineHeight = (YSZ / e->perpWallDist);

  		e->drawStart = -(e->lineHeight) / 2 + YSZ / 2;

  		if(e->drawStart < 0)
			e->drawStart = 0;

		e->drawEnd = e->lineHeight / 2 + YSZ / 2;

		if(e->drawEnd >= YSZ)
			e->drawEnd = YSZ - 1;

		printf("%d\n\n", e->drawStart);
		printf("%d\n", e->lineHeight);
		printf("%d\n", e->drawEnd);
		line_color(e);
		e->x++;
	}
}

int main(int ac, char **av)
{
	t_info *e;
	*av = NULL;
	ac = 0;
	int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	e = malloc(sizeof(t_info));
	ft_memset(e, 0, sizeof(t_info));
	e->loop = 0;
	set_up(e);
	while (!e->loop)
	{
		while(SDL_PollEvent(&e->event))
		{
			if (e->event.type == SDL_QUIT || e->event.key.keysym.sym == SDLK_ESCAPE)
			e->loop = 1;
		}
		calcul(e, worldMap);
 		SDL_RenderPresent(e->rend);
	}
    SDL_DestroyWindow(e->win);
    SDL_Quit();
    return(0);
}
