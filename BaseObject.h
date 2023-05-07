#ifndef BASEOJECT_H_INCLUDED
#define BASEOJECT_H_INCLUDED


#include "Bird.h"
#include "Pipe.h"
#include "Commonfuntion.h"
#include "item.h"
using namespace std;
class BaseOject
{
    public:
        int score;
        TTF_Font* font = TTF_OpenFont("font.ttf", 25);
        SDL_Color White = {255, 255, 255};
        int high_score = 0;
        bool loa = true;
       bool startmenu = true;
       bool option = false;
       bool highscore = false;
        int numberPlayMusic = 0;
        bool firstTime = true;
        int tmpMusic = 0;
        Mix_Chunk* click = Mix_LoadWAV("click.wav");
        Mix_Chunk* music = Mix_LoadWAV("fly.wav");
        Mix_Music* deadSound = Mix_LoadMUS("crash.wav");
        Mix_Chunk* backgroundSound = Mix_LoadWAV("nhacnen.mp3");
        bool paused = false;
        int level=0;
        float timed =0;
        bool day = true;
        int number_day=0;


        SDL_Texture *texture_background;
        SDL_Texture *texture_background_night;
        SDL_Texture *texture_ground;
        SDL_Texture *texture_pipe;
        SDL_Texture *texture_numbers[20];
        SDL_Texture *texture_gameover;
        SDL_Texture *texture_bird_Up;
        SDL_Texture *texture_bird_Mid;
        SDL_Texture *texture_bird_Down;
       SDL_Texture *texture_play;
       SDL_Texture*texture_item[2];
       SDL_Texture * texture_option;
       SDL_Texture* texture_hightscore;
       SDL_Texture* texture_bird_eat;
       SDL_Texture *texture_bird_eat2;
       SDL_Texture *texture_level;
       SDL_Texture *texture_loa;
       SDL_Texture*texture_noloa;
       SDL_Texture *texture_back;
       SDL_Texture * texture_flag;


        bool Running;

        BaseOject(const char *title, int _width, int _height);
       void menu();
        void Start();
        void Close();
        void update(bool jump, float elapsedTime, bool &gameover);
        void render();
        void gameOver();
        void init();
        void renderhightscore();
        void pause();
        void savehighscore();
        void Option();
        void renderoldhightscore();



    private:
        SDL_Renderer *grenderer;
        SDL_Window *gwindow;

        SDL_Event event;

        Bird *bird;
        item* _item;

        std::list<Pipe*> pipes;

        int ground1, ground2;

        bool gameStarted, gameover;

        void loadTextures();
};



#endif // BASEOJECT_H_INCLUDED
