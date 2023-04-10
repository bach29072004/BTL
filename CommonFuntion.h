#ifndef COMMONFUNTION_H_
#define COMMONFUNTION_H_


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <list>
#include <chrono>
#include <random>
#include <time.h>
#include <string>
#include <bits/stdc++.h>
#include <fstream>



static SDL_Window* gwindow = NULL;
static SDL_Renderer* grenderer = NULL;
static SDL_Event event;

const int WIDTH = 500;
const int  HEIGHT = 667;
const char* Tiles = "Flappy Dog";

const int  FPS = 60;
const int  frameDelay =  1000 / FPS;

const int GRAVITY= 90.0f;

const int BIRD_WIDTH =60;
const int BIRD_HEIGHT= 45;

const int PIPE_WIDTH = 80;
const int PIPE_WIDTH_SRC= 50;
const int PIPE_GAP =170;
const int PIPE_DISTANCE= 250;
const int PIPE_V =3;
const int PIPE_MIN_H =150;
const int PIPE_MAX_H =450;

const int ITEM_WIDTH = 80;
const int ITEM_HEIGHT = 80;
const int tiem_spaunt_item = 30;

const int GROUND_HEIGHT= 112;
const int GROUND_WIDTH =336;

#endif // COMMONFUNTION_H_
