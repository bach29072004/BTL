#ifndef PIPE_H_
#define PIPE_H_


#include <SDL.h>
#include "CommonFuntion.h"

struct Pipe
{

    SDL_Rect pipe_top_s, pipe_top_d, pipe_bottom_d, pipe_bottom_s;

    bool passed_pipe = true;
    Pipe(int x, int height_pipe)
    {
              pipe_top_d.x = x;
              pipe_top_d.y = 0;
              pipe_top_d.w = PIPE_WIDTH;
              pipe_top_d.h = HEIGHT - height_pipe ;

              pipe_top_s.x = 0;
              pipe_top_s.y = 0;
              pipe_top_s.w = PIPE_WIDTH_SRC;
              pipe_top_s.h = pipe_top_d.h;


              pipe_bottom_d.x = x;
              pipe_bottom_d.y = HEIGHT - height_pipe - PIPE_GAP;
              pipe_bottom_d.w = PIPE_WIDTH;
              pipe_bottom_d.h = height_pipe;

              pipe_bottom_s.x = 0;
              pipe_bottom_s.y = 0;
              pipe_bottom_s.w = PIPE_WIDTH_SRC;
              pipe_bottom_s.h = height_pipe;



              passed_pipe = false;
       }

       void render(SDL_Renderer *renderer, SDL_Texture *texture)
       {
              SDL_RenderCopy(renderer, texture, &pipe_bottom_s, &pipe_bottom_d);
              SDL_RenderCopyEx(renderer, texture, &pipe_top_s, &pipe_top_d, 0, NULL, SDL_FLIP_VERTICAL);
       }
};


#endif // PIPE_H_INCLUDED

