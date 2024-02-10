#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2_framerate.h"
#include "Block.h"
#include <math.h>

#define WALL_X 100.0

extern SDL_Window* window;
extern SDL_Renderer* render;

extern SDL_Event eve;
extern FPSmanager fps;
extern const Uint8* keystate;
extern bool leave;

extern TTF_Font* font;

extern bool finish;
extern int counter;
extern SDL_Texture* counter_texture;


SDL_Texture* renderText(std::string text, Uint8 r, Uint8 g, Uint8 b);
void init();
void free();
void collision(Block&a, Block& b);
