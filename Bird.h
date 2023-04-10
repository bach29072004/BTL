#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Pipe.h"
#include "CommonFuntion.h"
#include "item.h"

class Bird
{
    private:
        float Velocity;
        float Acceleration;

        SDL_Rect pos;

        SDL_Texture *Bird_UP;
        SDL_Texture *Bird_DOWN;
        SDL_Texture *Bird_MID;
        SDL_Texture *CurrentRenderingTexture;
        SDL_Renderer *Renderer;

        int Animation_Frames;


    public:
        int Score;
        Mix_Chunk* ScoreSound = Mix_LoadWAV("score.wav");
        Mix_Chunk * itemSound = Mix_LoadWAV("itemsound.wav");
        Bird(SDL_Texture *Bird_UP, SDL_Texture *Bird_MID, SDL_Texture *Bird_DOWN, SDL_Renderer *Renderer);
        void onit();
        void render();
        void update(bool jump, float elapsedTime);
        void animation();
        bool CollisionPipe(Pipe *pipe);
         int GetScore()
        {
            return Score;
        }
        bool Eatitem(item* item);
};

#endif // BIRD_H_INCLUDED


