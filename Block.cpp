#include "global.h"
#include "Block.h"
Block::Block() :mass(0.0), velocity(0.0)
{
	r = {0.0,0.0,0.0,0.0 };
}
Block::Block(float x, float y, float w, float h, float vel, double m)
{
	this->mass = m;
	this->velocity = vel;
	this->r = { x,y,w,h };
}
Block::~Block()
{

}
void Block::render()
{
	SDL_SetRenderDrawColor(::render, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderDrawRectF(::render, &r);
}
void Block::move(double time)
{
	r.x += time * velocity;
}