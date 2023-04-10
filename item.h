#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <SDL.h>
#include "CommonFuntion.h"
struct item
{
       SDL_Rect item_rect;
       bool eat_item;

       item(int item_x, int item_y){
              item_rect.x = item_x;
              item_rect.y = item_y;
              item_rect.w = ITEM_WIDTH;
              item_rect.h = ITEM_HEIGHT;
              eat_item = false;
       }

       void render(SDL_Renderer* render, SDL_Texture* texture)
       {
              SDL_RenderCopy(render,texture,NULL , &item_rect);
       }
};
#endif // ITEM_H_INCLUDED
