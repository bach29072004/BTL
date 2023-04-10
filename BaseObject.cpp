#include "BaseObject.h"
#include "Bird.h"
#include "CommonFuntion.h"
#include "Pipe.h"


using namespace std;
BaseObject::BaseObject()
{
    gwindow = SDL_CreateWindow(Tiles, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    LoadTexture();
    bird = new Bird(Texture_bird_UP,Texture_bird_MID,Texture_bird_DOWN,grenderer);

    Run = true;
    Gameover = false;

    groundtop = -WIDTH / 2;
    groundbot = WIDTH   / 2;

    srand(time(NULL));
}

void BaseObject::init()
{
    bird->onit();

    for(auto pipe : pipes)
        pipes.pop_front();

    pipes.push_back(new Pipe(WIDTH * 2 + PIPE_DISTANCE, rand() % 301 + 150));
    pipes.push_back(new Pipe(pipes.back()->pipe_bottom_d.x + PIPE_DISTANCE, rand() % 301 + 150));
    pipes.push_back(new Pipe(pipes.back()->pipe_bottom_d.x + PIPE_DISTANCE, rand() % 301 + 150));

    GameStarted = false;
       Gameover = false;

    render();
}

void BaseObject::renderHighScore(){
    string tmp = "High Score: " + to_string(high_score);
    SDL_Surface* Surface_HightScore = TTF_RenderText_Solid(Font, tmp.c_str() , Color);

    SDL_Texture* High_core_mess = SDL_CreateTextureFromSurface(grenderer, Surface_HightScore);

    SDL_Rect hight_score_rect;
    hight_score_rect.x = 0;
    hight_score_rect.y = 0;
    hight_score_rect.w = Surface_HightScore->w;
    hight_score_rect.h = Surface_HightScore->h;

    SDL_RenderCopy(grenderer, High_core_mess, NULL, &hight_score_rect);
    //cout << "D";
    SDL_FreeSurface(Surface_HightScore);
    SDL_DestroyTexture(High_core_mess);
}

void BaseObject::Start()
{
    init();

    auto t1 = chrono::system_clock::now();
    auto t2 = t1;
    // main game loop

    while(Run)
    {
        t1 = t2;
        t2 = chrono::system_clock::now();

        chrono::duration<float> dt = t2 - t1;

        bool jump = false;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                Run = false;

            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
                {
                    Mix_PlayChannel(-1,Music,0);
                    jump = GameStarted = true;
                    if(MusicFirstTime == false) MusicTMP = false;
                    if(MusicFirstTime == true && MusicTMP == 1) MusicFirstTime = false;
                }
        }
        //cout << gameStarted << " " << tmpMusic << " " << firstTime << endl;
        if(GameStarted == true && MusicTMP == 0 && MusicFirstTime == true) {
                MusicTMP = 1;
                Mix_PlayChannel(-1,BackGroundSound,0);
                PlayMusic++;
                MusicFirstTime = false;
                //cout << numberPlayMusic << "\n";
        }


        if(frameDelay > dt.count())
            SDL_Delay(frameDelay - dt.count());

        if(GameStarted)
        {
            update(jump, dt.count(), Gameover);
            if(Gameover)
                {
                    gameOver();
                }
        }
    }

    Close();
}

void BaseObject::update(bool jump, float elapsedTime, bool &gameover)
{
    bird->update(jump, elapsedTime);

    for(auto p : pipes)
    {
        p->pipe_bottom_d.x -= PIPE_V;
        p->pipe_top_d.x = p->pipe_bottom_d.x;

        if(p->pipe_bottom_d.x + p->pipe_bottom_d.w < 0)
        {
            pipes.pop_front();
            pipes.push_back(new Pipe(pipes.back()->pipe_bottom_d.x + PIPE_DISTANCE, rand() % 301 + 150));
        }

        if(bird->CollisionPipe(p))
            gameover = true;
    }

    groundbot -= PIPE_V;
    groundtop -= PIPE_V;

    if(groundbot + WIDTH < 0)
        groundbot = WIDTH - 10;
    if(groundtop + WIDTH < 0)
        groundtop = WIDTH - 10;

    render();
}

void BaseObject::gameOver()
{
    GameStarted = false;

    SDL_RenderCopy(grenderer, Texture_Gameover, NULL, new SDL_Rect{WIDTH / 2 - 96, HEIGHT / 3, 192, 42});
    SDL_RenderPresent(grenderer);
    if(GameStarted == false) Mix_PlayMusic(DeadSound,0);
    if(GameStarted == false) Mix_HaltChannel(-1);
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
        }
    }
    if(high_score < bird->Score) high_score = bird->Score;

    //cout << high_score << "\n";
    if(playagain)
        {
            MusicTMP = 0;
            MusicFirstTime = true;
            Start();
        }
    else
        {

            Run = false;
        }
}

void BaseObject::render()
{

    SDL_RenderClear(grenderer);

    // background
    SDL_RenderCopy(grenderer, Texture_Backround, NULL, NULL);

    // pipes
    for(auto pipe : pipes)
    {
        pipe->render(grenderer, Texture_Pipe);
    }

    // score
    if(bird->Score > 9)
    {
        SDL_RenderCopy(grenderer, Texture_Number[bird->Score / 10 % 10], NULL, new SDL_Rect{WIDTH / 2 - 20, 100, 40, 52});
        SDL_RenderCopy(grenderer, Texture_Number[bird->Score % 10], NULL, new SDL_Rect{WIDTH / 2 + 20, 100, 40, 52});
    }
    else
        SDL_RenderCopy(grenderer, Texture_Number[bird->Score], NULL, new SDL_Rect{WIDTH / 2, 100, 40, 52});

    // ground
    SDL_RenderCopy(grenderer, Texture_Ground, NULL, new SDL_Rect{groundbot, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});
    SDL_RenderCopy(grenderer, Texture_Ground, NULL, new SDL_Rect{groundtop, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});

    // player
    bird->render();
    renderHighScore();
    SDL_RenderPresent(grenderer);
}


void BaseObject::LoadTexture()
{
    Texture_Backround = IMG_LoadTexture(grenderer, "picture/background-day.png");
    Texture_Pipe = IMG_LoadTexture(grenderer, "picture/pipe.png");
    Texture_bird_MID = IMG_LoadTexture(grenderer, "picture/dog2.png");
    Texture_bird_UP = IMG_LoadTexture(grenderer, "picture/dog3.png");
    Texture_bird_DOWN = IMG_LoadTexture(grenderer, "picture/dog2.png");
    Texture_Ground = IMG_LoadTexture(grenderer, "picture/base.png");
    Texture_Gameover = IMG_LoadTexture(grenderer, "picture/gameover.png");
    Texture_item = IMG_LoadTexture(grenderer, "picture/item.png");


    for(int i = 0; i < 10; i++)
    {
        string path = "picture/" + to_string(i) + ".png";
        Texture_Number[i] = IMG_LoadTexture(grenderer, path.c_str());
    }
}
void BaseObject::SaveHightScore(){
       ofstream file_HightScore("hightscore.txt");
       file_HightScore << high_score;
}
void RenderOldScore()
{

}
void BaseObject::Close()
{
    SDL_Quit();
}
