#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Pipe.h"
#include "Commonfuntion.h"
#include "item.h"

class Bird
{
    private:
       float Velocity;
        float Acceleration;

       SDL_Rect pos;

        SDL_Texture *up;
        SDL_Texture *down;
        SDL_Texture *mid;
        SDL_Texture* birdeat;
        SDL_Texture* birdeatx2;
        SDL_Texture *CurrentRenderingTexture;
        SDL_Renderer *renderer;

        int Animation_Frames;


    public:

        int score;
       bool pause = false;
        Mix_Chunk* scoreSound = Mix_LoadWAV("score.wav");
        Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Texture*birdeat, SDL_Texture*birdeatx2, SDL_Renderer *renderer);
        int getScore()
        {
            return score;
        }
        void init();
        void render(item* _item);
        void update(bool jump, float elapsedTime);
        void animation();
        bool collisionDetector(Pipe *pipe, item*items);
        bool eat_item(item*_item);
        void velocitywhenpause();
};

#endif // BIRD_H_INCLUDED
