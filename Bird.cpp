#include "Bird.h"
#include <bits/stdc++.h>
using namespace std;
void Bird::onit()
{
    CurrentRenderingTexture = Bird_MID;
    Animation_Frames = 0;
    Score = 0;

    Velocity = 0.0f;
    Acceleration = 0.0f;

    pos.x = WIDTH /4;
    pos.y = HEIGHT / 2;
    pos.w = BIRD_WIDTH;
    pos.h = BIRD_HEIGHT;
}

Bird::Bird(SDL_Texture *Bird_UP, SDL_Texture *Bird_MID, SDL_Texture *Bird_DOWN, SDL_Renderer *renderer) :
                                                                             Bird_UP(Bird_UP), Bird_MID(Bird_MID), Bird_DOWN(Bird_DOWN), Renderer(Renderer)
{
    onit();
}
// bird jump
void Bird::update(bool JUMP, float ElapsedTime)
{
    ElapsedTime *= 5;
    if(JUMP)
    {
            Velocity = -GRAVITY;
            Acceleration =0;

    }
    else
    {
           Acceleration = GRAVITY ;

    }

    Velocity += Acceleration * ElapsedTime;
    pos.y += Velocity * ElapsedTime;
    if (item ->eat_item == true)
              Velocity =0;
}
// collision
bool Bird::CollisionPipe(Pipe *pipe)
{
       // Collision pipe
       if(pipe->pipe_top_d.x <= pos.x + pos.w && pipe->pipe_top_d.x + PIPE_WIDTH >= pos.x + pos.w)
              if(pos.y < pipe->pipe_top_d.y + pipe->pipe_top_d.h || pos.y + pos.h > pipe->pipe_bottom_d.y)
                     return true;

       // Collision ground
       if(pos.y + pos.h > HEIGHT - GROUND_HEIGHT)
              return true;

       // Collision ceilling
       if(pos.y < 0)
              return true;

       if(!pipe->passed_pipe && pipe->pipe_top_d.x + PIPE_WIDTH < pos.x)
       {
              pipe->passed_pipe = true;
              Score++;
              if(pipe->passed_pipe == true) Mix_PlayChannel(-1,ScoreSound,0);
       }

       return false;
}
// eat item
bool Bird::Eatitem(item* item)
{
       if(item->item_rect.x <= pos.x + pos.w && item->item_rect.x + ITEM_WIDTH >= pos.x + pos.w)
              if(pos.y < item->item_rect.y + item->item_rect.h || pos.y + pos.h > item->item_rect.y)
                     return true;
       if(!item->eat_item )
       {
              item ->eat_item =true;
              if(item->eat_item ==true) Mix_PlayChannel(-1, itemSound,0);
       }
       return false;
}

void Bird::render()
{
       animation();

    if(Velocity == 0)
        SDL_RenderCopy(grenderer, Bird_MID, NULL, &pos);
    else if(Velocity < 50)
        SDL_RenderCopyEx(grenderer, CurrentRenderingTexture, NULL, &pos, -30.0, NULL, SDL_FLIP_NONE);
    else if(Velocity >= 50 && Velocity < 200)
        SDL_RenderCopyEx(grenderer, CurrentRenderingTexture, NULL, &pos, 30.0, NULL, SDL_FLIP_NONE);
    else if(Velocity >= 200)
        SDL_RenderCopyEx(grenderer, Bird_MID, NULL, &pos, 90.0, NULL, SDL_FLIP_NONE);

}

void Bird::animation()
{
    Animation_Frames++;

    if(Animation_Frames == 5)
        CurrentRenderingTexture = Bird_DOWN;
    else if(Animation_Frames == 15)
        CurrentRenderingTexture = Bird_MID;
    else if(Animation_Frames == 20)
    {
        Animation_Frames = 0;
        CurrentRenderingTexture = Bird_UP;
    }
}

