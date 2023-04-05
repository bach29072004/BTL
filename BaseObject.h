#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include "Bird.h"
#include "Pipe.h"
#include "Commonfuntion.h"

class BaseObject
{
    public:

        int score;
        TTF_Font* font = TTF_OpenFont("font.ttf", 25);
        SDL_Color White = {255, 255, 255};
        int high_score = 0;

        int numberPlayMusic = 0;
        bool firstTime = true;
        int tmpMusic = 0;
        Mix_Chunk* music = Mix_LoadWAV("fly.wav");
        Mix_Music* deadSound = Mix_LoadMUS("crash.wav");
        Mix_Chunk* backgroundSound = Mix_LoadWAV("nhacnen.mp3");


        SDL_Texture *texture_background;
        SDL_Texture *texture_ground;
        SDL_Texture *texture_pipe;
        SDL_Texture *texture_numbers[20];
        SDL_Texture *texture_gameover;
        SDL_Texture *texture_bird_Up;
        SDL_Texture *texture_bird_Mid;
        SDL_Texture *texture_bird_Down;


        bool Running;

        BaseObject(const char *title, int _width, int _height);

        void Start();
        void Close();
        void update(bool jump, float elapsedTime, bool &gameover);
        void render();
        void gameOver();
        void init();
        void renderHighScore();
        void SaveHighScore();

    private:
        SDL_Renderer *grenderer;
        SDL_Window *gwindow;

        SDL_Event event;

        Bird *bird;

        std::list<Pipe*> pipes;

        int ground1, ground2;

        bool gameStarted, gameover;

        void loadTextures();
};



#endif // GAME_H_INCLUDED

