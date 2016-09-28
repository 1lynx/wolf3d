#include "../header/wolf.h"

void poll_event(t_info *e)
{
  while(SDL_PollEvent(&e->event))
  {
    if (e->event.type == SDL_QUIT || e->event.key.keysym.sym == SDLK_ESCAPE)
        e->loop = 1;
    if (e->event.key.keysym.sym == SDLK_UP)
        move_forward(e);
    if (e->event.key.keysym.sym == SDLK_DOWN)
        move_back(e);
    if (e->event.key.keysym.sym == SDLK_RIGHT)
        turn_right(e);
    if (e->event.key.keysym.sym == SDLK_LEFT)
        turn_left(e);
    if (e->event.type == SDL_MOUSEMOTION)
    {
        if (e->event.motion.xrel < 0 && e->event.motion.x <= XSZ / 2)
            turn_left(e);
        else if (e->event.motion.xrel > 0 && e->event.motion.x >= XSZ / 2)
            turn_right(e);
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
