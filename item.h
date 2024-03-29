#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED


#include <SDL.h>
#include "Commonfuntion.h"

struct item
{
       SDL_Rect rect_item;
       bool eat ;
       int type;
       float time_dis = TIME_ITEM_OVER;
       item(int x ,int y,int t){
              rect_item.x = x;
              rect_item.y = y;
              rect_item.w =  40;
              rect_item.h = 40;
              eat = false;
              type = t;
       }
       void render_item(SDL_Renderer * render , SDL_Texture *texture){
              if(!eat)
                     SDL_RenderCopy(render, texture,NULL , &rect_item);
       }

};
#endif // ITEM_H_INCLUDED
