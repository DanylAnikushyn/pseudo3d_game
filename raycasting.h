#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "map.h"
#include "textures_manager.h"

void draw_rect(SDL_Renderer *renderer, Uint32 x, Uint32 y, Uint32 w, Uint32 h, 
									Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

void ray_cast(SDL_Renderer *renderer, TexturesManager *texture_manager, Map *map, float player_pos_x, float player_pos_y,
		float player_angle);
#endif
