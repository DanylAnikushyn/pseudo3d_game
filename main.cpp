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
      	SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
      	SDL_Rect rect;
      	rect.w = AppConfig::windows_rect.w;
      	rect.h = AppConfig::windows_rect.h;
      	rect.x = 0;
      	rect.y = 0;
      	SDL_RenderFillRect(renderer, &rect);
		
		interface->displayFPS(renderer, (int)FPS);
    	
		map.drawMiniMap(renderer, {(int)player.getPosition().x, (int)player.getPosition().y}, player.getAngle());

		SDL_Rect w_from;
		w_from.w = 1157; w_from.h = 495; w_from.x = 0; w_from.y = 0;
		SDL_Rect w_to;
		w_to.w = 900; w_to.h = 400; w_to.x = 300; w_to.y = AppConfig::windows_rect.h - w_to.h + 100; 

		weapon_manager->drawWeapon(renderer, WeaponType::Minigan, w_from, w_to);

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