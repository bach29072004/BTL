#include "Bird.h"
#include <bits/stdc++.h>
using namespace std;
void Bird::init()
{
    CurrentRenderingTexture = mid;
    Animation_Frames = 0;
    score = 0;

    Velocity = 0.0f;
    Acceleration = 0.0f;

    pos.x = WIDTH / 3 - 32;
    pos.y = HEIGHT / 2;
    pos.w = BIRD_WIDTH;
    pos.h = BIRD_HEIGHT;
}

Bird::Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Texture*birdeat, SDL_Texture* birdeatx2,SDL_Renderer *renderer) :
                     up(up), mid(mid),down(down), birdeat(birdeat), birdeatx2(birdeatx2),renderer(renderer)
{
       init();
}

void Bird::update(bool jump, float elapsedTime)
{
    elapsedTime *= 5;
    if(jump)
    {
        Acceleration = 0.0f;
        Velocity = -GRAVITY;
    }
    else
    {
        Acceleration += GRAVITY * elapsedTime;
    }

    if(Acceleration >= GRAVITY)
        Acceleration = GRAVITY;

    Velocity += Acceleration * elapsedTime;
    pos.y += Velocity * elapsedTime;
}

bool Bird::collisionDetector(Pipe *pipe,item* items)
{
       int left_bird = pos.x;
       int right_bird = pos.x + pos.w;
       int top_bird = pos.y;
       int bot_bird = pos.y + pos.h;

       int left_toppipe = pipe->top_dst.x;
       int right_toppipe = pipe->top_dst.x + pipe->top_dst.w;
       int top_toppipe = pipe->top_dst.y;
       int bot_toppipe = pipe->top_dst.y + pipe->top_dst.h;

       int left_botpipe = pipe->bottom_dst.x;
       int right_botpipe = pipe->bottom_dst.x + pipe->bottom_dst.w;
       int top_botpipe = pipe->bottom_dst.y;
       int bot_botpipe = pipe->bottom_dst.y + pipe->bottom_dst.h;

       // pipe top
       if ( left_toppipe > left_bird && left_toppipe < right_bird)
       {
              if (top_toppipe > top_bird && top_toppipe < bot_bird)
              {
                     return true;
              }
       }

       if ( left_toppipe > left_bird && left_toppipe < right_bird)
       {
              if (bot_toppipe > top_bird && bot_toppipe < bot_bird)
              {
                     return true;
              }
       }

       if (right_toppipe > left_bird && right_toppipe < right_bird)
       {
              if (top_toppipe > top_bird && top_toppipe < bot_bird)
              {
                     return true;
              }
       }

       if (right_toppipe > left_bird && right_toppipe < right_bird)
       {
              if (bot_toppipe > top_bird && bot_toppipe < bot_bird)
              {
                     return true;
              }
       }

    //pipe bot
    if ( left_botpipe > left_bird && left_botpipe < right_bird)
       {
              if (top_botpipe > top_bird && top_botpipe < bot_bird)
              {
                     return true;
              }
       }

       if ( left_botpipe > left_bird && left_botpipe < right_bird)
       {
              if (bot_botpipe > top_bird && bot_botpipe < bot_bird)
              {
                     return true;
              }
       }

       if (right_botpipe > left_bird && right_botpipe < right_bird)
       {
              if (top_botpipe > top_bird && top_botpipe < bot_bird)
              {
                     return true;
              }
       }

       if (right_botpipe > left_bird && right_botpipe < right_bird)
       {
              if (bot_botpipe > top_bird && bot_botpipe < bot_bird)
              {
                     return true;
              }
       }

 // gruond
       if(bot_bird > HEIGHT - GROUND_HEIGHT)
              return true;


       if(top_bird < 0)
              return true;

       if(!pipe->passed && pipe->top_dst.x + PIPE_WIDTH < pos.x)
       {
              pipe->passed = true;
              if (items->eat&&items->type==2)
                     score+=2;
              else score+=1;
              if(pipe->passed == true) Mix_PlayChannel(-1,scoreSound,0);

       }

    return false;
}

bool Bird::eat_item(item*_item){
       int left_bird = pos.x;
       int right_bird = pos.x + pos.w;
       int top_bird = pos.y;
       int bot_bird = pos.y + pos.h;

       int left_item = _item->rect_item.x;
       int right_item = _item->rect_item.x + _item->rect_item.w;
       int top_item = _item->rect_item.y;
       int bot_item = _item->rect_item.y + _item->rect_item.h;

       if (left_bird > left_item && left_bird < right_item)
       {
              if (top_bird > top_item && top_bird < bot_item)
              {
                     return true;
              }
       }

       if (left_bird > left_item && left_bird < right_item)
       {
              if (bot_bird > top_item && bot_bird < bot_item)
              {
              return true;
              }
       }

       if (right_bird > left_item && right_bird < right_item)
       {
              if (top_bird > top_item && top_bird < bot_item)
              {
                     return true;
              }
       }

       if (right_bird > left_item && right_bird < right_item)
       {
              if (bot_bird > top_item && bot_bird < bot_item)
              {
                     return true;
              }
       }
       return false;
}
void Bird::render(item* _item)
{
       animation();
       if (_item->eat ==false)
       {
              if(Velocity == 0)
                     SDL_RenderCopy(renderer, mid, NULL, &pos);
              else if(Velocity < 60)
                     SDL_RenderCopyEx(renderer, CurrentRenderingTexture, NULL, &pos, -30.0, NULL, SDL_FLIP_NONE);
              else if(Velocity >= 60 && Velocity < 200)
                     SDL_RenderCopyEx(renderer, CurrentRenderingTexture, NULL, &pos, 30.0, NULL, SDL_FLIP_NONE);
              else if(Velocity >= 200)
                     SDL_RenderCopyEx(renderer, mid, NULL, &pos, 90.0, NULL, SDL_FLIP_NONE);
       }
       else{
              if (_item->type==1)
                     SDL_RenderCopy(renderer,birdeat,NULL,&pos);
              else
                     SDL_RenderCopy(renderer,birdeatx2,NULL,&pos);
       }
}


void Bird::animation()
{
    Animation_Frames++;

    if(Animation_Frames == 5)
        CurrentRenderingTexture = down;
    else if(Animation_Frames == 15)
        CurrentRenderingTexture = mid;
    else if(Animation_Frames == 20)
    {
        Animation_Frames = 0;
        CurrentRenderingTexture = up;
    }
}
