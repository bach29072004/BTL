#include "Bird.h"
#include <bits/stdc++.h>
using namespace std;
void Bird::init()
{
    CurrentRenderingTexture = bird_mid;
    frames = 0;
    score = 0;

    Velocity = 0.0f;
    Acceleration = 0.0f;

    pos.x = WIDTH / 3 - 32;
    pos.y = HEIGHT / 2;
    pos.w = BIRD_WIDTH;
    pos.h = BIRD_HEIGHT;
}

Bird::Bird(SDL_Texture *bird_up, SDL_Texture *bird_mid, SDL_Texture *bird_down, SDL_Texture*birdeat, SDL_Texture* birdeatx2,SDL_Renderer *renderer) :
                     bird_up(bird_up), bird_mid(bird_mid),bird_down(bird_down), birdeat(birdeat), birdeatx2(birdeatx2),renderer(renderer)
{
       init();
}
void Bird::velocitywhenpause(){
       Velocity =0;
}
void Bird::update(bool jump, float elapsedTime)
{
       if(flag != 2){
        elapsedTime = 0;
        flag++;
        flag %= 3;
    }
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
       if (left_bird > left_toppipe && left_bird < right_toppipe)
       {
              if (top_bird > top_toppipe && top_bird < bot_toppipe)
              {
                     return true;
              }
       }

       if (left_bird > left_toppipe && left_bird < right_toppipe)
       {
              if (bot_bird >  top_toppipe && bot_bird < bot_toppipe)
              {
              return true;
              }
       }

       if (right_bird > left_toppipe && right_bird < right_toppipe)
       {
              if (top_bird >  top_toppipe && top_bird < bot_toppipe)
              {
                     return true;
              }
       }

       if (right_bird > left_toppipe && right_bird < right_toppipe)
       {
              if (bot_bird >  top_toppipe && bot_bird < bot_toppipe)
              {
                     return true;
              }
       }

    //pipe bot
    if (left_bird > left_botpipe && left_bird < right_botpipe)
       {
              if (top_bird > top_botpipe && top_bird < bot_botpipe)
              {
                     return true;
              }
       }

       if (left_bird > left_botpipe && left_bird < right_botpipe)
       {
              if (bot_bird > top_botpipe && bot_bird < bot_botpipe)
              {
              return true;
              }
       }

       if (right_bird > left_botpipe && right_bird < right_botpipe)
       {
              if (top_bird > top_botpipe && top_bird < bot_botpipe)
              {
                     return true;
              }
       }

       if (right_bird > left_botpipe && right_bird < right_botpipe)
       {
              if (bot_bird > top_botpipe && bot_bird < bot_botpipe)
              {
                     return true;
              }
       }


 // gruond
       if(pos.y + pos.h > HEIGHT - GROUND_HEIGHT)
              return true;


       if(pos.y < 0)
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
       if (_item->eat ==true && _item->type==3){
              pos.w = BIRD_WIDTH/2;
              pos.h = BIRD_HEIGHT/2;
       }
       else {
              pos.w =BIRD_WIDTH;
              pos.h = BIRD_HEIGHT;
       }

       animation();
       if (_item->eat ==true)
       {
              if (_item->type==1)
              SDL_RenderCopy(renderer,birdeat,NULL,&pos);
              else if (_item->type ==2)
              SDL_RenderCopy(renderer,birdeatx2,NULL,&pos);
              else if (_item->type==3)
                     SDL_RenderCopy(renderer,bird_mid,NULL,&pos);
       }

       else{

              if(Velocity == 0)
                     SDL_RenderCopy(renderer, bird_mid, NULL, &pos);
              else if(Velocity < 60)
                     SDL_RenderCopyEx(renderer, CurrentRenderingTexture, NULL, &pos, -30.0, NULL, SDL_FLIP_NONE);
              else if(Velocity >= 60 && Velocity < 200)
                     SDL_RenderCopyEx(renderer, CurrentRenderingTexture, NULL, &pos, 30.0, NULL, SDL_FLIP_NONE);
              else if(Velocity >= 200)
                     SDL_RenderCopyEx(renderer, bird_mid, NULL, &pos, 90.0, NULL, SDL_FLIP_NONE);
       }
}


void Bird::animation()
{
    frames++;

    if(frames == 5)
        CurrentRenderingTexture = bird_down;
    else if(frames == 15)
        CurrentRenderingTexture = bird_mid;
    else if(frames == 20)
    {
        frames = 0;
        CurrentRenderingTexture = bird_up;
    }
}
