#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <SDL.h>
#include "Commonfuntion.h"

struct item
{
       SDL_Rect item_;
       bool eat_item;
       item(int x , int y)
       {
              item_.x = x;
              item_.y = y;
              item_.w = ITEM_WIDTH;
              item_.h = ITEM_HEIGHT;

              eat_item = false;
       }
       void render_item(SDL_Renderer* render, SDL_Texture* texture)
       {

       SDL_RenderCopy(render , texture, NULL,item_);
       }
};
