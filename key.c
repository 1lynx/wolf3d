#include "header/wolf.h"

void poll_event(t_info *e)
{
  while(SDL_PollEvent(&e->event))
  {
    if (e->event.type == SDL_QUIT || e->event.key.keysym.sym == SDLK_ESCAPE)
        e->loop = 1;
    if (e->event.key.keysym.sym == SDLK_UP)
    {
      if(!(e->tab[(int)(e->posX + e->dirX * e->moveSpeed)][(int)(e->posY)]))
          e->posX += e->dirX * e->moveSpeed;
      if(!(e->tab[(int)(e->posX)][(int)(e->posY + e->dirY * e->moveSpeed)]))
          e->posY += e->dirY * e->moveSpeed;
    }
    if (e->event.key.keysym.sym == SDLK_DOWN)
    {
      if(!(e->tab[(int)(e->posX + e->dirX * e->moveSpeed)][(int)(e->posY)]))
          e->posX -= e->dirX * e->moveSpeed;
      if(!(e->tab[(int)(e->posX)][(int)(e->posY + e->dirY * e->moveSpeed)]))
          e->posY -= e->dirY * e->moveSpeed;
    }
    if (e->event.key.keysym.sym == SDLK_RIGHT)
    {
      e->oldDirX = e->dirX;
      e->dirX = e->dirX * cos(-e->rotSpeed) - e->dirY * sin(-e->rotSpeed);
      e->dirY = e->oldDirX * sin(-e->rotSpeed) + e->dirY * cos(-e->rotSpeed);
      e->oldPlaneX = e->planeX;
      e->planeX = e->planeX * cos(-e->rotSpeed) - e->planeY * sin(-e->rotSpeed);
      e->planeY = e->oldPlaneX * sin(-e->rotSpeed) + e->planeY * cos(-e->rotSpeed);
    }
    if (e->event.key.keysym.sym == SDLK_LEFT)
    {
      e->oldDirX = e->dirX;
      e->dirX = e->dirX * cos(e->rotSpeed) - e->dirY * sin(e->rotSpeed);
      e->dirY = e->oldDirX * sin(e->rotSpeed) + e->dirY * cos(e->rotSpeed);
      e->oldPlaneX = e->planeX;
      e->planeX = e->planeX * cos(e->rotSpeed) - e->planeY * sin(e->rotSpeed);
      e->planeY = e->oldPlaneX * sin(e->rotSpeed) + e->planeY * cos(e->rotSpeed);
    }
    // if (e->event.key.keysym.sym == SDLK_a)
    // {
    //   modify_tab(e->tab);
    // }


  }
}

void timer(t_info *e)
{
  e->oldtime = e->newtime;
  e->newtime = SDL_GetTicks();
  e->frametime = (e->newtime - e->oldtime) / 1000.0;
  e->moveSpeed = e->frametime * 10.0;
  e->rotSpeed = e->frametime * 3.0;
}
