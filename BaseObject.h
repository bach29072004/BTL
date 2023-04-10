#ifndef COMMONFUNTION_H_INCLUDED
#define COMMONFUNTION_H_INCLUDED

#include "CommonFuntion.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Bird.h"

class BaseObject
{
private:

        Bird *bird;

        std::list<Pipe*> pipes;

        int groundbot, groundtop;

        bool GameStarted, Gameover;

        void LoadTexture();
public:
        int PlayMusic = 0;
        bool MusicFirstTime = true;
        int MusicTMP = 0;
        Mix_Chunk* Music = Mix_LoadWAV("fly.wav");
        Mix_Music* DeadSound = Mix_LoadMUS("crash.wav");
        Mix_Chunk* BackGroundSound = Mix_LoadWAV("nhacnen.mp3");
        int score;
        TTF_Font* Font = TTF_OpenFont("font.ttf", 30);
        SDL_Color Color = {255, 255, 255};
        int high_score = 0;
        SDL_Texture *Texture_Backround;
        SDL_Texture *Texture_Ground;
        SDL_Texture *Texture_bird_UP;
        SDL_Texture *Texture_bird_MID;
        SDL_Texture *Texture_bird_DOWN;
        SDL_Texture *Texture_Pipe;
        SDL_Texture *Texture_Number[10];
        SDL_Texture *Texture_Gameover;
        SDL_Texture *Texture_item;

        bool Run;

        BaseObject();

        void Start();
        void update(bool jump, float elapsedTime, bool &gameover);
        void render();
        void gameOver();
        void init();
        void renderHighScore();
       void Close();
       void SaveHightScore();
       void RenderOldScore();


};



#endif // GAME_H_INCLUDED
