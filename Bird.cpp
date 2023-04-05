#include "Bird.h"
#include <bits/stdc++.h>
using namespace std;
void Bird::init()
{
    currentRenderingTexture = mid;
    animationFrames = 0;
    score = 0;

    velocity = 0.0f;
    acceleration = 0.0f;

    pos.x = WIDTH / 3 - 32;
    pos.y = HEIGHT / 2;
    pos.w = BIRD_WIDTH;
    pos.h = BIRD_HEIGHT;
}

Bird::Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Renderer *renderer) : up(up), mid(mid), down(down), renderer(renderer)
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

bool Bird::collisionDetector(Pipe *pipe)
{
    if(pipe->top_dst.x <= pos.x + pos.w && pipe->top_dst.x + PIPE_WIDTH >= pos.x + pos.w)
        if(pos.y < pipe->top_dst.y + pipe->top_dst.h || pos.y + pos.h > pipe->bottom_dst.y)
            return true;

    if(pos.y + pos.h > HEIGHT - GROUND_HEIGHT)
        return true;


    if(pos.y < 0)
        return true;

    if(!pipe->passed && pipe->top_dst.x + PIPE_WIDTH < pos.x)
    {
        pipe->passed = true;
        score++;
        if(pipe->passed == true) Mix_PlayChannel(-1,scoreSound,0);

    }

    return false;
}

void Bird::render()
{
    animation();

    if(Velocity == 0)
        SDL_RenderCopy(renderer, mid, NULL, &pos);
    else if(Velocity < 60)
        SDL_RenderCopyEx(renderer, currentRenderingTexture, NULL, &pos, -30.0, NULL, SDL_FLIP_NONE);
    else if(Velocity >= 60 && Velocity < 200)
        SDL_RenderCopyEx(renderer, currentRenderingTexture, NULL, &pos, 30.0, NULL, SDL_FLIP_NONE);
    else if(Velocity >= 200)
        SDL_RenderCopyEx(renderer, mid, NULL, &pos, 90.0, NULL, SDL_FLIP_NONE);

}

void Bird::animation()
{
    Animation_Frames++;

    if(Animation_Frames == 5)
        currentRenderingTexture = down;
    else if(Animation_Frames == 15)
        currentRenderingTexture = mid;
    else if(Animation_Frames == 20)
    {
        Animation_Frames = 0;
        currentRenderingTexture = up;
    }
}
