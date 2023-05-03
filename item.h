#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED


#include <SDL.h>
#include "Commonfuntion.h"

struct item
{
       SDL_Rect rect_item;
       item(int x ,int y){
              rect_item.x = x;
              rect_item.y = y;
              rect_item.w =  40;
              rect_item.h = 40;
       }
       void render_item(SDL_Renderer * render , SDL_Texture *texture){
              SDL_RenderCopy(render, texture,NULL , &rect_item);
       }

};
#endif // ITEM_H_INCLUDED
