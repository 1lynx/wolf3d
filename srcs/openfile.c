#include "../header/wolf.h"

void	open_file(t_info *i, char *filename)
{
	int		fd;
	char	*line;
	int		c;

	c = 0;
	fd = open(filename, O_RDONLY);
	i->tab = (int **)malloc(sizeof(int *) * 24);
	while ((get_next_line(fd, &line)) > 0)
	{
		i->tab[c] = get_int_tab(line);
		c++;
	}
	i->tab[c] = NULL;
}

int		*get_int_tab(char *str)
{
	int		i;
	char	**tmp;
	int		*tab;

	tab = NULL;
	i = 0;
	tmp = ft_strsplit(str, ' ');
	tab = (int *)malloc(sizeof(int) * count_col(tmp));
	while (tmp[i])
	{
		check_char(*tmp[i]);
		tab[i] = ft_atoi(tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (tab);
}

int		count_col(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_char(char c)
{
	if (ft_isdigit(c) || c == ' ' || c == '-')
		;
	else
		FDF_ERROR;
}

t_color **loadtexture(t_info *e, char *str)
{
	t_color **texture;
	int i = 0;
	int j = 0;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	Uint32 pixel;
	e->gtex = SDL_LoadBMP(str);
	texture = (t_color **)malloc(sizeof(t_color *) * e->gtex->w);
	while (i < e->gtex->h)
	{
		j = 0;
		texture[i] = (t_color *)malloc(sizeof(t_color) * e->gtex->w);
		while(j < e->gtex->w)
		{
			pixel = getpixel(e->gtex, i, j);
			SDL_GetRGBA(pixel, e->gtex->format, &r, &g, &b, &a);
			texture[i][j].r = r;
			texture[i][j].g = g;
			texture[i][j].b = b;
			texture[i][j].a = a;
			j++;
		}
		i++;
	}
	SDL_FreeSurface(e->gtex);
	return(texture);
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
