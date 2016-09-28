#include "../header/wolf.h"


void calcul(t_info *e)
{
	e->x = 0;
	while(e->x < XSZ)
	{
		re_calc(e);
		raydir(e);
		while (e->hit == 0)
		{
  		hit(e);
		}
		side(e);
		texture_calcul(e);
		e->x++;
	}
}

void clean_up(t_info *e)
{
	SDL_DestroyWindow(e->win);
	SDL_Quit();
}


int main(int ac, char **av)
{
	t_info *e;
	ac = 0;
	e = malloc(sizeof(t_info));
	ft_memset(e, 0, sizeof(t_info));
	open_file(e, av[1]);
	e->loop = 0;
	set_up_value(e);
	set_up(e);
	while (!e->loop)
	{
		timer(e);
		poll_event(e);
		calcul(e);
 		SDL_RenderPresent(e->rend);
	}
  clean_up(e);
  return(0);
}
