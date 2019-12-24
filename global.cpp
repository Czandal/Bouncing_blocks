#include "global.h"

SDL_Window* window;
SDL_Renderer* render;

SDL_Event eve;
FPSmanager fps;
const Uint8* keystate = nullptr;
bool leave = 0;

TTF_Font* font = nullptr;

bool finish = 0;
int counter = 0;
SDL_Texture* counter_texture = nullptr;

SDL_Texture* renderText(std::string text, Uint8 r, Uint8 g, Uint8 b)
{
	if (font != nullptr)
	{
		SDL_Color color = { r,g,b };
		color.a = 0xff;
		SDL_Surface* s = TTF_RenderText_Blended(font, text.c_str(), color);
		SDL_Texture* result = SDL_CreateTextureFromSurface(render, s);
		SDL_FreeSurface(s);
		return result;
	}
	return nullptr;
}

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	font = TTF_OpenFont("arial.ttf", 100);

	window = SDL_CreateWindow("Bounicng Blocks and PI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	keystate = nullptr;

	SDL_initFramerate(&fps);
	fps.rate = 60;
}

void free()
{
	SDL_DestroyTexture(counter_texture);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
}

void collision(Block &a, Block& b)
{
	float u = a.velocity;
	a.velocity = (u*(a.mass-b.mass)+2.0*b.mass*b.velocity)/ (a.mass + b.mass);
	b.velocity = (b.velocity * (b.mass - a.mass) + 2.0 * a.mass * u) / (a.mass + b.mass);
}