#include "global.h"
#include "Block.h"
int main(int argc, char*argv[])
{
	double m1, m2;
	std::cin >> m1;
	std::cin >> m2;
	init();
	SDL_Rect counter_pos = { 700,25,100,50};
	Block left(150.0, 700.0,m1, m1, 0.0,m1);
	left.r.y -= left.r.h;
	Block right(200.0+ left.r.h, 700.0,m2, m2, -10.0,m2);
	right.r.y -= right.r.h;
	while (!leave)
	{
		{//event handling
			if (SDL_PollEvent(&eve))
			{
				while (SDL_PollEvent(&eve))
				{
					if (eve.type == SDL_QUIT)
					{
						leave = 1;
					}
				}
			}
			keystate = SDL_GetKeyboardState(nullptr);
			if (keystate[SDL_SCANCODE_ESCAPE])
			{
				leave = 1;
			}
			{//movement
				double time = 0.05;
 				if (!finish)
				{
					while (time > 0.0)
					{
						if ((right.velocity < 0.0 && left.velocity >= 0.0))
						{
							double c1 = (right.r.x - left.r.x - left.r.w) / (abs(right.velocity) + abs(left.velocity));
							if (c1 <= time)
							{
								left.move(c1);
								right.move(c1);
								time -= c1;
								collision(left, right);
								counter++;
							}
							else
							{
								left.move(time);
								right.move(time);
								time -= time;
							}
						}
						else if (left.velocity < 0.0 && right.velocity>=0.0)
						{
							double c2 = abs((left.r.x - WALL_X) / left.velocity);
							if (c2 <= time)
							{
								left.move(c2);
								right.move(c2);
								time -= c2;
								left.velocity *= -1;
								counter++;
							}
							else
							{
								left.move(time);
								right.move(time);
								time -= time;
							}
						}
						else if (left.velocity < 0.0 && right.velocity < 0.0)
						{
							double c1=0.0;
							if (left.velocity < right.velocity)
							{
								c1 = INFINITY;
							}
							else
							{
								c1 = (right.r.x - left.r.x - left.r.w) / abs((double)(right.velocity - left.velocity));
							}
							double c2 = abs((left.r.x - WALL_X) / left.velocity);
							if (c1 <= time && c2 <= time && c1 > 0)
							{
								if (c1 < c2)
								{
									left.move(c1);
									right.move(c1);
									time -= c1;
									collision(left, right);
									counter++;
								}
								else
								{
									left.move(c2);
									right.move(c2);
									time -= c2;
									left.velocity *= -1;
									counter++;
								}
							}
							else if (c1 <= time && c1 > 0)
							{
								left.move(c1);
								right.move(c1);
								time -= c1;
								collision(left, right);
								counter++;
							}
							else if (c2 <= time)
							{
								left.move(c2);
								right.move(c2);
								time -= c2;
								left.velocity *= -1;
								counter++;
							}
							else
							{
								left.move(time);
								right.move(time);
								time -= time;
							}
						}
						else
						{
							if (left.velocity < right.velocity)
							{
								finish = 1;
								left.move(time);
								right.move(time);
								time -= time;
							}
							else
							{
								double c1 = (right.r.x - left.r.x - left.r.w) / (left.velocity - right.velocity);
								if (c1 <= time)
								{
									left.move(c1);
									right.move(c1);
									time -= c1;
									collision(left, right);
									counter++;
								}
								else
								{
									left.move(time);
									right.move(time);
									time -= time;
								}
							}
						}
					}
				}
				else
				{
					right.move(time);
					left.move(time);
				}
			}
		}
		{//render
			SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xff);
			SDL_RenderFillRect(render, nullptr);
			left.render();
			right.render();
			SDL_SetRenderDrawColor(render, 0xff, 0xff, 0xff, 0xff);
			SDL_RenderDrawLine(render,100,0,100,700);
			SDL_RenderDrawLine(render,800,700,100,700);
			if (counter_texture != nullptr)
			{
				SDL_DestroyTexture(counter_texture);
			}
			counter_texture = renderText(std::to_string(counter), 0xff, 0xff, 0xff);
			SDL_RenderCopy(render, counter_texture, nullptr, &counter_pos);
			SDL_RenderPresent(render);
		}
		SDL_framerateDelay(&fps);
	}
	std::cout <<"Numver of collisions: "<< counter;
	free();
	return 0;
}