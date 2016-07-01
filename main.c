#include "header/wolf.h"

void calcul(t_info *e)
{
	e->x = 0;
	while(e->x < XSZ)
	{
		re_calc(e);
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
  			if (e->tab[e->mapX][e->mapY] > 0)
				e->hit = 1;
		}

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
		line_color(e);
		e->x++;
	}
}

int main(int ac, char **av)
{
	t_info *e;
	ac = 0;
	e = malloc(sizeof(t_info));
	ft_memset(e, 0, sizeof(t_info));
	open_file(e, av[1]);
	e->loop = 0;
	set_up(e);
	set_up_value(e);
	while (!e->loop)
	{
		timer(e);
		poll_event(e);
		calcul(e);
 		SDL_RenderPresent(e->rend);
	}
    SDL_DestroyWindow(e->win);
    SDL_Quit();
    return(0);
}
