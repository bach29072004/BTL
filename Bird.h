#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Pipe.h"
#include "Commonfuntion.h"

class Bird
{
    private:
        float Velocity;
        float Acceleration;

        SDL_Rect pos;

        SDL_Texture *up;
        SDL_Texture *down;
        SDL_Texture *mid;
        SDL_Texture *CurrentRenderingTexture;
        SDL_Renderer *renderer;

        int Animation_Frames;


    public:
        int score;
        Mix_Chunk* scoreSound = Mix_LoadWAV("score.wav");
        Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Renderer *renderer);
        int getScore()
        {
            return score;
        }
        void init();
        void render();
        void update(bool jump, float elapsedTime);
        void animation();
        bool collisionDetector(Pipe *pipe);
};

#endif // BIRD_H_INCLUDED
