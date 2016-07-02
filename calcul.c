#include "header/wolf.h"

void turn_left(t_info *e)
{
  e->oldDirX = e->dirX;
  e->dirX = e->dirX * cos(e->rotSpeed) - e->dirY * sin(e->rotSpeed);
  e->dirY = e->oldDirX * sin(e->rotSpeed) + e->dirY * cos(e->rotSpeed);
  e->oldPlaneX = e->planeX;
  e->planeX = e->planeX * cos(e->rotSpeed) - e->planeY * sin(e->rotSpeed);
  e->planeY = e->oldPlaneX * sin(e->rotSpeed) + e->planeY * cos(e->rotSpeed);
}

void turn_right(t_info* e)
{
  e->oldDirX = e->dirX;
  e->dirX = e->dirX * cos(-e->rotSpeed) - e->dirY * sin(-e->rotSpeed);
  e->dirY = e->oldDirX * sin(-e->rotSpeed) + e->dirY * cos(-e->rotSpeed);
  e->oldPlaneX = e->planeX;
  e->planeX = e->planeX * cos(-e->rotSpeed) - e->planeY * sin(-e->rotSpeed);
  e->planeY = e->oldPlaneX * sin(-e->rotSpeed) + e->planeY * cos(-e->rotSpeed);
}

void move_back(t_info *e)
{
  if(!(e->tab[(int)(e->posX + e->dirX * e->moveSpeed)][(int)(e->posY)]))
      e->posX -= e->dirX * e->moveSpeed;
  if(!(e->tab[(int)(e->posX)][(int)(e->posY + e->dirY * e->moveSpeed)]))
      e->posY -= e->dirY * e->moveSpeed;
}

void move_forward(t_info *e)
{
  if(!(e->tab[(int)(e->posX + e->dirX * e->moveSpeed)][(int)(e->posY)]))
      e->posX += e->dirX * e->moveSpeed;
  if(!(e->tab[(int)(e->posX)][(int)(e->posY + e->dirY * e->moveSpeed)]))
      e->posY += e->dirY * e->moveSpeed;
}
