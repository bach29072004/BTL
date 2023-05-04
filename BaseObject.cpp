#include "BaseObject.h"
#include "Bird.cpp"

#include <bits/stdc++.h>
using namespace std;
BaseOject::BaseOject(const char *title, int width, int height)
{
    gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    loadTextures();

    bird = new Bird(texture_bird_Down, texture_bird_Mid, texture_bird_Up,texture_bird_eat, grenderer);

    Running = true;
    gameover = false;

    ground1 = -WIDTH / 2;
    ground2 = WIDTH   / 2;

    srand(time(NULL));
}

void BaseOject::init()
{
       bird->init();

       for(auto pipe : pipes)
              pipes.pop_front();

       pipes.push_back(new Pipe(WIDTH * 2 + PIPE_DISTANCE, rand() % 301 + 150 ));
       pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 150));
       pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 150));
       _item = new item(WIDTH * 2 + PIPE_DISTANCE,rand() % 301 + 150,2);
       gameStarted = false;
       gameover = false;

       render();
}
void BaseOject::menu(){
       SDL_RenderClear(grenderer);
       SDL_RenderCopy(grenderer, texture_background, NULL, NULL);
       SDL_RenderCopy(grenderer,texture_play,NULL, new SDL_Rect{150,100,200,100});
       SDL_RenderCopy(grenderer,texture_option,NULL,new SDL_Rect{150,250,200,100});
       SDL_RenderCopy(grenderer,texture_hightscore,NULL,new SDL_Rect{150,400,200,100});
       SDL_RenderPresent(grenderer);
}

void BaseOject::renderandsaveHighScore(){
       string tmp = "High Score: " + to_string(high_score);
       ofstream output("high_score.txt", ios::ate);
       output << high_score << endl;
       output.close();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, tmp.c_str() , White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(grenderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(grenderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void BaseOject::Start()
{

    init();

    auto t1 = chrono::system_clock::now();
    auto t2 = t1;
    // main game loop

       int t_;
    while(Running)
    {
        t1 = t2;
        t2 = chrono::system_clock::now();

        chrono::duration<float> dt = t2 - t1;
        bool jump = false;
        while(SDL_PollEvent(&event))
        {
              int x = event.motion.x, y = event.motion.y;
              if(event.type == SDL_QUIT)
                     Running = false;
              if(startmenu == false){
              if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
                                                               (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
                {
                    Mix_PlayChannel(-1,music,0);
                    jump = gameStarted = true;
                    if(firstTime == false) tmpMusic = false;
                    if(firstTime == true && tmpMusic == 1) firstTime = false;
                }
              }

              if(startmenu == false){
                     if(gameStarted == true && tmpMusic == 0 && firstTime == true) {
                            tmpMusic = 1;
                            Mix_PlayChannel(-1,backgroundSound,0);
                            numberPlayMusic++;
                            firstTime = false;

                     }
              }
              if(startmenu == true){
                     menu();
                     if (event.type == SDL_MOUSEBUTTONDOWN&& x>=150&&x<=150+200 && y>=100 && y <=100+100){
                            startmenu = false;
                     }
              }
       }


        if(frameDelay > dt.count())
              SDL_Delay(frameDelay - dt.count());


        if(gameStarted)
        {
            update(jump, dt.count(), gameover);
            if(gameover)
                {
                    gameOver();
                }
        }

    }
    Close();
}

void BaseOject::update(bool jump, float elapsedTime, bool &gameover)
{
       //bird
       bird->update(jump, elapsedTime);

       //pipe
       for(auto p : pipes)
       {
              p->bottom_dst.x -= PIPE_V;
              p->top_dst.x = p->bottom_dst.x;

       if(p->bottom_dst.x + p->bottom_dst.w < 0)
       {
              pipes.pop_front();
              pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 150));
       }

       if(bird->collisionDetector(p,_item))
              if (_item->eat)
                     _item-> eat = false;
              else
                    gameover = true;
       }

       //item
       _item->rect_item.x-=PIPE_V;

       if(bird->score%11==0)
       {
              _item=new item(500,300,2);
       }

       if(bird->eat_item(_item))
       {
              _item->eat = true;
       }

       ground1 -= PIPE_V;
       ground2 -= PIPE_V;

       if(ground1 + WIDTH < 0)
              ground1 = WIDTH - 10;
       if(ground2 + WIDTH < 0)
              ground2 = WIDTH - 10;

       render();
}

void BaseOject::gameOver()
{
    gameStarted = false;

    SDL_RenderCopy(grenderer, texture_gameover, NULL, new SDL_Rect{WIDTH / 2 - 96, HEIGHT / 3, 192, 42});
    SDL_RenderPresent(grenderer);
    if(gameStarted == false) Mix_PlayMusic(deadSound,0);
    if(gameStarted == false) Mix_HaltChannel(-1);
    SDL_Delay(1000);

    bool wait = true, playagain = false;
    while(wait)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                wait = false;

            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
                wait = false, playagain = true;
                startmenu = true;
        }
    }
    if(high_score < bird->score) high_score = bird->score;


    if(playagain)
        {
            tmpMusic = 0;
            firstTime = true;
            Start();
        }
    else
        {

            Running = false;
        }
}

void BaseOject::render()
{

    SDL_RenderClear(grenderer);

    // background
    SDL_RenderCopy(grenderer, texture_background, NULL, NULL);

    //item
    _item->render_item(grenderer,texture_item2);
    for(auto pipe : pipes)
    {
        pipe->render_pipe(grenderer, texture_pipe);
    }

    // score
    if(bird->score > 9)
    {
        SDL_RenderCopy(grenderer, texture_numbers[bird->score / 10 % 10], NULL, new SDL_Rect{WIDTH / 2 - 20, 100, 40, 52});
        SDL_RenderCopy(grenderer, texture_numbers[bird->score % 10], NULL, new SDL_Rect{WIDTH / 2 + 20, 100, 40, 52});
    }
    else
        SDL_RenderCopy(grenderer, texture_numbers[bird->score], NULL, new SDL_Rect{WIDTH / 2, 100, 40, 52});

    // ground
    SDL_RenderCopy(grenderer, texture_ground, NULL, new SDL_Rect{ground1, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});
    SDL_RenderCopy(grenderer, texture_ground, NULL, new SDL_Rect{ground2, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});

    // player
    bird->render(_item);
    renderandsaveHighScore();
    SDL_RenderPresent(grenderer);
}


void BaseOject::loadTextures()
{
    texture_background = IMG_LoadTexture(grenderer, "picture/background-day.png");
    texture_pipe = IMG_LoadTexture(grenderer, "picture/pipe.png");
    texture_bird_Mid = IMG_LoadTexture(grenderer, "picture/dog.png");
    texture_bird_Down = IMG_LoadTexture(grenderer, "picture/dog.png");
    texture_bird_Up = IMG_LoadTexture(grenderer, "picture/dog.png");
    texture_ground = IMG_LoadTexture(grenderer, "picture/base.png");
    texture_gameover = IMG_LoadTexture(grenderer, "picture/gameover.png");
    texture_item1 = IMG_LoadTexture(grenderer, "picture/item.png");
    texture_play = IMG_LoadTexture(grenderer,"picture/play.png");
    texture_option = IMG_LoadTexture(grenderer,"picture/option.png");
    texture_hightscore = IMG_LoadTexture(grenderer,"picture/score.png");
    texture_bird_eat = IMG_LoadTexture(grenderer,"picture/dogeat.png");
    texture_item2 =IMG_LoadTexture(grenderer,"picture/itemx2.png");
    texture_bird_eat2 = IMG_LoadTexture(grenderer,"picture/dogx2.png");


    for(int i = 0; i < 10; i++)
    {
        string path = "picture/" + to_string(i) + ".png";
        texture_numbers[i] = IMG_LoadTexture(grenderer, path.c_str());
    }
}

void BaseOject::Close()
{

    SDL_Quit();
}





