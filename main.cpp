#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "appconfig.h"
#include "raycasting.h"
#include "player.h"
#include "map.h"
#include "player.h"
#include "textures_manager.h"
#include "weapon_manager.h"
#include "interface.h"

int main(int argc, char* argv[])
{
	SDL_Window *window = SDL_CreateWindow("Pseudo 3d game",
										  SDL_WINDOWPOS_UNDEFINED,
										  SDL_WINDOWPOS_UNDEFINED,	
										  AppConfig::windows_rect.w, 
										  AppConfig::windows_rect.h,
										  SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	srand(0);
	if (renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		return -1;
	}
	if (window == nullptr)
	{
		SDL_Log("Could not create a window: %s", SDL_GetError());
		return -1;
	}

	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		SDL_Log("Couldn't initialize IMG: %s", SDL_GetError());
		return -1;
	}
	if(TTF_Init() == -1) 
	{
		SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
		return -1;
	}
	

	Player player;
	Map map;
	TexturesManager *texture_manager = TexturesManager::get(renderer);
	WeaponManager *weapon_manager = WeaponManager::get(renderer);
	Interface *interface = Interface::get();

	double FPS;
	Uint32 time1, time2, dt, fps_time = 0, fps_count = 0, delay = 15;
	time1 = SDL_GetTicks();
	while (true)
	{
		time2 = SDL_GetTicks();
		dt = time2 - time1;
		time1 = time2;
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;	
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					break;
				}
			}
			player.move(&map);
		}
		SDL_RenderClear(renderer);	
		texture_manager->draw_background(renderer, player.getAngle());
		ray_cast(renderer, texture_manager, &map, player.getPosition().x, player.getPosition().y, player.getAngle());
		interface->displayFPS(renderer, (int)FPS);
    
		map.drawMiniMap(renderer, {(int)player.getPosition().x, (int)player.getPosition().y}, player.getAngle());

		

		weapon_manager->drawWeapon(renderer, WeaponType::Minigan);
		
		SDL_Delay(delay);

		//FPS
		fps_time += dt;
		fps_count++;
		if(fps_time > 200)
		{
			FPS = (double)fps_count / fps_time * 1000;
			if (FPS > 60) delay++;
			else if (delay > 0) delay--;
			fps_time = 0;
			fps_count = 0;
		}

		SDL_RenderPresent(renderer);
	}
	Interface::destroy();
	TexturesManager::destroy();
	WeaponManager::destroy();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}