#pragma once
#include <SDL.h>
class Block
{
public:
	SDL_FRect r;
	double mass;
	float velocity;
	Block();
	Block(float x,float y,float w, float h, float vel,double m);
	~Block();
	void render();
	void move(double time);
};

