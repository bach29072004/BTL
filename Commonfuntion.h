#ifndef Commonfuntion_H_INCLUDED
#define Commonfuntion_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <list>
#include <chrono>
#include <random>
#include <time.h>
#include <string>
#include <fstream>
#include <algorithm>

#define WIDTH 500
#define HEIGHT 667



#define BIRD_WIDTH 50
#define BIRD_HEIGHT 50

#define PIPE_WIDTH 80
#define PIPE_WIDTH_SRC 55
#define PIPE_GAP 200
#define PIPE_DISTANCE 300
#define PIPE_V 3

#define PIPE_MIN_H 150
#define PIPE_MAX_H 450

#define GROUND_HEIGHT 100
#define GROUND_WIDTH 300

#define TIME_SPAWN_ITEM 15
#define TIME_ITEM_OVER 8

#define GRAVITY 90.0f

#define FPS 60
#define frameDelay 1000 / FPS


#endif // DEFS_H_INCLUDED
