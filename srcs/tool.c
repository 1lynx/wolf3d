#include "../header/wolf.h"

void 	set_up_value(t_info *e)
{
	e->posX = 12;
	e->posY = 2;
	e->dirX = -1;
	e->dirY = 0;
	e->planeX = 0;
	e->planeY = 0.66;
	e->newtime = 0;
	e->oldtime = 0;
	e->texture_wall = loadtexture(e, "assets/sol.bmp");
	e->texture_floor = loadtexture(e, "assets/muri.bmp");
	// print_tab(e);
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

	//draw sky
  SDL_SetRenderDrawColor(e->rend, 51, 204, 255, 255);
	trace_line_pixel(e, e->x, 0, e->drawStart);
	//draw floor
  // SDL_SetRenderDrawColor(e->rend, 255, 255, 255, 255);
	// trace_line_pixel(e, e->x, e->drawEnd, YSZ);
}

void trace_line_pixel(t_info *e, int x, int y, int y2)
{
  while(y <= y2)
  {
    SDL_RenderDrawPoint(e->rend, x, y);
    y++;
  }
}

void trace_texture_wall(t_info *e)
{
	int y;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	y = e->drawStart;
	while(y < e->drawEnd)
	{
		int d = y * 256 - YSZ * 128 + e->lineHeight * 128;  //256 and 128 factors to avoid floats
    e->texY = ((d * texHeight) / e->lineHeight) / 256;
		r = e->texture_wall[(int)e->texX][(int)e->texY].r;
		g = e->texture_wall[(int)e->texX][(int)e->texY].g;
		b = e->texture_wall[(int)e->texX][(int)e->texY].b;
		a = e->texture_wall[(int)e->texX][(int)e->texY].a;
		SDL_SetRenderDrawColor(e->rend, r, g, b, a);
		SDL_RenderDrawPoint(e->rend, e->x, y);
		y++;
	}
}

void trace_texture_floor(t_info *e)
{
	int y;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	y = e->drawEnd;
	while (y < YSZ)
	{
		e->distWall = e->perpWallDist;
		e->currentDist = YSZ / (2* y - YSZ);// distance
		e->weight = e->currentDist / e->distWall;// coef
		e->currentFloorX = e->weight * e->floorXWall + (1.0 - e->weight) * e->posX;// position sur X
		e->currentFloorY = e->weight * e->floorYWall + (1.0 - e->weight) * e->posY;// position sur Y
		e->floorTexX =(int)(e->currentFloorX * texWidth) %texWidth;// position texel sur X
		e->floorTexY =(int)(e->currentFloorY * texHeight) %texHeight;// position texel sur Y
		// printf("\ndistWall  %f", e->distWall);
		// printf("\ncurrentDist  %f", e->currentDist);
		// printf("\nweight  %f", e->weight);
		// printf("\ne->currentFloorX  %f", e->currentFloorX);
		// printf("\ncurrentFloorY    %f", e->currentFloorY);
		r = e->texture_floor[(int)e->floorTexX][(int)e->floorTexY].r;
		g = e->texture_floor[(int)e->floorTexX][(int)e->floorTexY].g;
		b = e->texture_floor[(int)e->floorTexX][(int)e->floorTexY].b;
		a = e->texture_floor[(int)e->floorTexX][(int)e->floorTexY].a;
		SDL_SetRenderDrawColor(e->rend, r, g, b, a);
		SDL_RenderDrawPoint(e->rend, e->x, y);
		// SDL_SetRenderDrawColor(e->rend, r, g, b, a);
		// SDL_RenderDrawPoint(e->rend, e->x, (YSZ - y - 1));
		y++;
	}

}
