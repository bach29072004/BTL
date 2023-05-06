#include "BaseObject.h"
#include "Bird.cpp"

#include <bits/stdc++.h>
using namespace std;
BaseOject::BaseOject(const char *title, int width, int height)
{
    gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    loadTextures();

    bird = new Bird(texture_bird_Down, texture_bird_Mid, texture_bird_Up,texture_bird_eat,texture_bird_eat2, grenderer);

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
       pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE+level*40, rand() % 301 + 150));
       pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE+level*40, rand() % 301 + 150));
       _item = new item(WIDTH ,rand() % 301 + 150,2);
       gameStarted = false;
       gameover = false;

       render();
}
void BaseOject::menu(){
       if(option == false && highscore==false){
       SDL_RenderClear(grenderer);
       SDL_RenderCopy(grenderer, texture_background, NULL, NULL);
       SDL_RenderCopy(grenderer,texture_play,NULL, new SDL_Rect{150,100,200,100});
       SDL_RenderCopy(grenderer,texture_option,NULL,new SDL_Rect{150,250,200,100});
       SDL_RenderCopy(grenderer,texture_hightscore,NULL,new SDL_Rect{150,400,200,100});
       SDL_RenderPresent(grenderer);
       }
       else if (option == true ){
              Option();
       }
       else if (highscore == true){
              renderoldhightscore();
       }
}
void BaseOject::Option(){
       SDL_RenderClear(grenderer);
       SDL_RenderCopy(grenderer, texture_background, NULL, NULL);
       SDL_RenderCopy(grenderer,texture_level,NULL,new SDL_Rect{50,50,400,357});
       if (loa== true)
              SDL_RenderCopy(grenderer,texture_loa, NULL , new SDL_Rect{400,600,50,50});
       else
              SDL_RenderCopy(grenderer,texture_noloa, NULL , new SDL_Rect{400,600,50,50});
       if(level==0){
              SDL_RenderCopy(grenderer,texture_flag,NULL,new SDL_Rect{90,70,40,40});
       }
       else if(level==1){
              SDL_RenderCopy(grenderer,texture_flag,NULL,new SDL_Rect{90,160,40,40});
       }
       else if(level==2){
              SDL_RenderCopy(grenderer,texture_flag,NULL,new SDL_Rect{90,250,40,40});
       }
       else if(level==3){
              SDL_RenderCopy(grenderer,texture_flag,NULL,new SDL_Rect{90,340,40,40});
       }
      SDL_RenderCopy(grenderer,texture_back,NULL,new SDL_Rect{20,600,60,60});
        SDL_RenderPresent(grenderer);
}
void BaseOject::renderoldhightscore(){
       ifstream infile;
       infile.open("high_score.txt",ios::in);
       int *score_ = new int[50];
       fill(score_,score_+50,0);
       int i=0;
       while (!infile.eof()){
              infile>>score_[i];
              i++;
       }
       sort(score_,score_+50);
       SDL_RenderClear(grenderer);
       SDL_RenderCopy(grenderer, texture_background, NULL, NULL);
       for (int j = 49;j>=40;j--){
               if(score_[j] > 9)
              {
                     SDL_RenderCopy(grenderer, texture_numbers[score_[j]/10%10], NULL, new SDL_Rect{WIDTH / 2-10 , (50-j)*50, 30, 39});
                     SDL_RenderCopy(grenderer, texture_numbers[score_[j]%10], NULL, new SDL_Rect{WIDTH / 2+10 , (50-j)*50, 30, 39});
              }
              else
                     SDL_RenderCopy(grenderer, texture_numbers[score_[j]], NULL, new SDL_Rect{WIDTH / 2 , (50-j)*50, 30, 39});
       }
       SDL_RenderCopy(grenderer,texture_back,NULL,new SDL_Rect{20,600,60,60});
       SDL_RenderPresent(grenderer);
       infile.close();
       delete[] score_;
       score_ = NULL;
}
void BaseOject::renderhightscore(){
       string tmp = "High Score: " + to_string(high_score);

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
              if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                     Mix_PlayChannel(-1,click,0);
              }
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
                     if (event.type == SDL_MOUSEBUTTONDOWN&& x>=150&&x<=350 && y>=100 && y <=200&&!option&&!highscore){
                            startmenu = false;
                     }
                     if (event.type == SDL_MOUSEBUTTONDOWN&& x>=150&&x<=350 && y>=250 && y <=350&&!highscore){
                            option =true;
                     }
                     if (event.type == SDL_MOUSEBUTTONDOWN&& x>=150&&x<=350&&y>=400 && y<=500&&!option){
                            highscore = true;
                     }
                     if(option == true){
                            if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=130&&x<=360&&y>=60&&y<=120){
                                   level =0;
                            }
                            if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=130&&x<=360&&y>=150&&y<=210){
                                   level =1;
                            }
                            if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=130&&x<=360&&y>=240&&y<=300){
                                   level =2;
                            }
                            if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=130&&x<=360&&y>=330&&y<=390){
                                   level =3;
                            }
                             if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=20&&x<=80&&y>=600&&y<=660){
                                   option = false;
                             }
                             if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=400&&x<=450&&y>=600&&y<=650){
                                   if(loa)
                                          loa = false;
                                   else
                                          loa = true;
                             }
                     }
                     if(highscore==true){
                            if ( event.type == SDL_MOUSEBUTTONDOWN&&x>=20&&x<=80&&y>=600&&y<=660){
                                   highscore = false;
                             }
                     }
              }
              if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
                     paused =true;
                     pause();
              }
       }



        if(frameDelay > dt.count())
              SDL_Delay(frameDelay - dt.count());


        if(gameStarted)
        {
              if (loa==false){
                     Mix_Pause(-1);
                     Mix_PauseMusic();
               }
            update(jump, dt.count(), gameover);
            timed = timed + dt.count();
            _item->time_dis = _item->time_dis - dt.count();
            cout << timed << endl;
            if(gameover)
                {
                    gameOver();
                }
        }

    }
    Close();
}
void BaseOject::pause(){
       while (paused){
              while (SDL_PollEvent(&event)){
                     if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
                            paused = false;
                            return;
                     }
              }
       }
}

void BaseOject::update(bool jump, float elapsedTime, bool &gameover)
{
       //bird
       bird->update(jump, elapsedTime);

       //pipe
       for(auto p : pipes)
       {
              p->bottom_dst.x -= (PIPE_V+level);
              p->top_dst.x = p->bottom_dst.x;

       if(p->bottom_dst.x + p->bottom_dst.w < 0)
       {
              pipes.pop_front();
              pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE+level*40, rand() % 301 + 150));
       }

       if(bird->collisionDetector(p,_item) )
              gameover = true;
       }
       if (_item->eat ==true && _item->type ==1 && _item->time_dis >0){
              gameover =false;
       }

       //item
       _item->rect_item.x-=PIPE_V;

       if (_item->time_dis<=0){
              _item->eat = false;
       }

       if(timed >=TIME_SPAWN_ITEM)
       {
              int type_item =rand()%2+1;
              _item = new item(WIDTH,330,type_item);
              timed =0;
       }

       if(bird->eat_item(_item))
       {
              _item->eat = true;
       }

       ground1 -= (PIPE_V+level);
       ground2 -= (PIPE_V+level);

       if(ground1 + WIDTH < 0)
              ground1 = WIDTH - 10;
       if(ground2 + WIDTH < 0)
              ground2 = WIDTH - 10;

       render();
}

void BaseOject::gameOver()
{

    gameStarted = false;

    SDL_RenderCopy(grenderer, texture_gameover, NULL, new SDL_Rect{WIDTH / 2 -96, HEIGHT/2-100, 192, 42});
    SDL_RenderCopy(grenderer, texture_bird_Mid, NULL, new SDL_Rect{WIDTH / 2 -100, HEIGHT / 2, 200, 200});
    if(bird->score > 9)
    {
        SDL_RenderCopy(grenderer, texture_numbers[bird->score / 10 % 10], NULL, new SDL_Rect{WIDTH / 2-80 , HEIGHT / 2+48, 80, 104});
        SDL_RenderCopy(grenderer, texture_numbers[bird->score % 10], NULL, new SDL_Rect{WIDTH / 2 , HEIGHT / 2+48, 80, 104});
    }
    else
        SDL_RenderCopy(grenderer, texture_numbers[bird->score], NULL, new SDL_Rect{WIDTH / 2 - 40, HEIGHT / 2+48, 80, 104});
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
    if (high_score!=0)
              savehighscore();
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
    _item->render_item(grenderer,texture_item[_item->type-1]);
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
    renderhightscore();
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
    texture_play = IMG_LoadTexture(grenderer,"picture/play.png");
    texture_option = IMG_LoadTexture(grenderer,"picture/option.png");
    texture_hightscore = IMG_LoadTexture(grenderer,"picture/score.png");
    texture_bird_eat = IMG_LoadTexture(grenderer,"picture/dogeat.png");
    texture_bird_eat2 = IMG_LoadTexture(grenderer,"picture/dogx2.png");
    texture_item[0] = IMG_LoadTexture(grenderer, "picture/item.png");
     texture_item[1] =IMG_LoadTexture(grenderer,"picture/itemx2.png");
     texture_level = IMG_LoadTexture(grenderer,"picture/level.png");
     texture_loa = IMG_LoadTexture(grenderer,"picture/loa.png");
     texture_noloa=IMG_LoadTexture(grenderer,"picture/noloa.png");
       texture_back= IMG_LoadTexture(grenderer,"picture/back.png");
       texture_flag = IMG_LoadTexture(grenderer,"picture/flag.png");

    for(int i = 0; i < 10; i++)
    {
        string path = "picture/" + to_string(i) + ".png";
        texture_numbers[i] = IMG_LoadTexture(grenderer, path.c_str());
    }
}

void BaseOject::savehighscore(){
       ofstream outfile;
       outfile.open("high_score.txt",ios::app);
       outfile << high_score << endl;
       outfile.close();
}

void BaseOject::Close()
{
       SDL_Quit();
}





