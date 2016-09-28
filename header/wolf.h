/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchampda <cchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:40:08 by cchampda          #+#    #+#             */
/*   Updated: 2016/09/28 16:42:09 by cchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WOLF_H
# define WOLF_H
#include "SDL2/SDL.h"
#include "../libft/libft.h"
#include <stdio.h>

# define XSZ 700
# define YSZ 500
# define mapWidth 8
# define mapHeight 100
# define texHeight 256
# define texWidth 256
# define FDF_ERROR { ft_putstr("Error, invalid file"); exit(-1); }

typedef struct s_color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
}							 t_color;
typedef struct s_info
{
	SDL_Window *win;
	SDL_Surface *gtex;
	SDL_Renderer *rend;
	SDL_Event event;
	int	loop;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double newtime;
	double oldtime;
	double frametime;
	double cameraX;
	double rayPosX;
	double rayPosY;
	double rayDirX;
	double rayDirY;
	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int x;
	int drawStart;
	int drawEnd;
	int lineHeight;
	int			**tab;
	int		ti;
	t_color 	**texture_wall;
	t_color   **texture_floor;
	double floorXWall;
	double floorYWall;
	double weight;
	double currentFloorX;
	double currentFloorY;
	double floorTexX;
	double floorTexY;
	double distWall;
	double distPlayer;
	double currentDist;
	double wallX;
	double texX;
	double texY;
}				t_info;


int set_up(t_info *e);
void timer(t_info *e);
void poll_event(t_info *e);
void 	set_up_value(t_info *e);
void re_calc(t_info *e);
void calcul(t_info *e);
void line_color(t_info *e);
int	*get_int_tab(char *str);
void	open_file(t_info *i, char *filename);
int		count_col(char **tab);
void	check_char(char c);
void turn_left(t_info *e);
void turn_right(t_info* e);
void move_back(t_info *e);
void move_forward(t_info *e);
void side(t_info *e);
void hit(t_info *e);
void raydir(t_info *e);
void trace_line_pixel(t_info *e, int x, int y, int y2);
void clean_up(t_info *e);
t_color **loadtexture(t_info *e, char *str);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void texture_calcul(t_info *e);
void trace_texture_wall(t_info *e);
void trace_texture_floor(t_info *e);








#endif
