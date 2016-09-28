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

void raydir(t_info *e)
{
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
}

void hit(t_info *e)
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
  if (e->tab[e->mapX][e->mapY] > 0)
  	e->hit = 1;
}

void side(t_info *e)
{
  if (e->side == 0)
    e->perpWallDist = (e->mapX - e->rayPosX + (1 - e->stepX) / 2) / e->rayDirX;
  else
    e->perpWallDist = (e->mapY - e->rayPosY + (1 - e->stepY) / 2) / e->rayDirY;
  e->lineHeight = (int)(YSZ / e->perpWallDist);
  e->drawStart = -e->lineHeight / 2 + YSZ / 2;
  if (e->drawStart < 0)
    e->drawStart = 0;
  e->drawEnd = e->lineHeight / 2 + YSZ / 2;
  if (e->drawEnd >= YSZ)
    e->drawEnd = YSZ - 1;
}

void texture_calcul(t_info *e)
{
    if (e->side == 0)
			e->wallX = e->rayPosY + e->perpWallDist * e->rayDirY;
    else
			e->wallX = e->rayPosX + e->perpWallDist * e->rayDirX;
    e->wallX -= floor((e->wallX));
    e->texX = (int)(e->wallX * texWidth);
    if(e->side == 0 && e->rayDirX > 0)
			e->texX = texWidth - e->texX - 1;
    if(e->side == 1 && e->rayDirY < 0)
			e->texX = texWidth - e->texX - 1;
		trace_texture_wall(e);
		//Le mur peut être orienté de 4 manières
		if (e->side == 0 && e->rayDirX > 0)
		{// nord
				e->floorXWall = e->mapX;
				e->floorYWall = e->mapY + e->wallX;
		}
		else if (e->side == 0 && e->rayDirX < 0)
		{	// sud
			e->floorXWall = e->mapX + 1.0;
			e->floorYWall = e->mapY + e->wallX;
		}
		else if (e->side == 1 && e->rayDirY > 0)
		{
			// est
			e->floorXWall = e->mapX + e->wallX;
			e->floorYWall = e->mapY;
		}
		else
		{
			// ouest
			e->floorXWall = e->mapX + e->wallX;
			e->floorYWall = e->mapY + 1.0;
		}
		line_color(e);
		trace_texture_floor(e);

}
