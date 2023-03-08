#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
const int screen_WIDTH = 1024;
const int screen_HEIGHT = 768;
const string WINDOW_TITLE = "SDL test";
void logSDLerror(std :: ostream & os,
                 const std:: string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer );
void quitSDL(SDL_Window* window, SDL_Renderer* renderer );
void WaitUntilKeyPressed();
SDL_Texture* LoadTexture(string path , SDL_Renderer* renderer);
int main(int argc , char* argv[]){
       SDL_Window *window=NULL;
       SDL_Renderer *renderer=NULL;
       initSDL(window, renderer);
       // draw;
       SDL_Texture* backround = LoadTexture("backround.png",renderer);
       SDL_RenderCopy(renderer,backround,NULL,NULL);

       SDL_Texture* hellob= LoadTexture("bird.png",renderer);
       SDL_Rect blockrect ;
       SDL_QueryTexture(hellob,NULL,NULL, &blockrect.w , &blockrect.h);
       blockrect.x =100;
       blockrect.y =100;
       blockrect.w = 100;
       blockrect.h = 100;
       SDL_RenderCopy(renderer,hellob,NULL, &blockrect);

       SDL_RenderPresent(renderer);

       WaitUntilKeyPressed();
       quitSDL(window, renderer);

}

void logSDLerror(std::ostream & os,
                 const std:: string &msg, bool fatal ){
       os << msg << "Error: " <<SDL_GetError() << endl;
       if (fatal){
              SDL_Quit();
              exit(1);
       }
                 }
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer ){
       if (SDL_Init(SDL_INIT_EVERYTHING) !=0){
              logSDLerror(std::cout, "SDL init " , true);
       }
      window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,screen_WIDTH,screen_HEIGHT, SDL_WINDOW_SHOWN);
      if (window == nullptr) logSDLerror (std :: cout , "createwindow", true);
       renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED |
                                       SDL_RENDERER_PRESENTVSYNC);
       if (renderer == nullptr) logSDLerror(std:: cout ,"createrenderer",true);
       SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
       SDL_RenderSetLogicalSize(renderer , screen_WIDTH, screen_HEIGHT);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer ){
       SDL_DestroyRenderer(renderer);
       SDL_DestroyWindow(window);
       SDL_Quit;
}
void WaitUntilKeyPressed(){
       SDL_Event e;
       while (true){
              if (SDL_WaitEvent(&e) !=0 && e.type == SDL_KEYDOWN || e.type == SDL_QUIT)
                     return ;
              SDL_Delay(100);
       }

}

SDL_Texture* LoadTexture(string path , SDL_Renderer* renderer){
       SDL_Texture* texture = NULL;
       SDL_Surface* loadsurface = IMG_Load(path.c_str());
       if (loadsurface == nullptr) {
              cout << "error loadimg: " << IMG_GetError() << endl;
       }
       else{
              texture = SDL_CreateTextureFromSurface(renderer,loadsurface);
              if (texture == nullptr){
                     cout << "errol load texture" << SDL_GetError();
                     SDL_FreeSurface(loadsurface);
              }
              return texture;
       }
}
