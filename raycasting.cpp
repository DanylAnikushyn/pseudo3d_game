#include "raycasting.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "appconfig.h"

static SDL_Point mapping(SDL_Point point) 
{
	point.x = std::floor(point.x / AppConfig::tile) * AppConfig::tile;
	point.y = std::floor(point.y / AppConfig::tile) * AppConfig::tile;
	return point;  
}

void draw_rect(SDL_Renderer *renderer, Uint32 x, Uint32 y, Uint32 w, Uint32 h, 
									Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_Rect r;
	r.w = w; r.h = h; r.x = x; r.y = y;
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &r);
}

void ray_cast(SDL_Renderer *renderer, TexturesManager * texture_manager, Map *map, float player_pos_x, float player_pos_y,
			float player_angle)
{
	SDL_Point mapped_pos = mapping({(int)std::round(player_pos_x), (int)std::round(player_pos_y)});
	float current_angle = player_angle - AppConfig::half_fov;
	for (int nray = 0; nray < AppConfig::num_rays; ++nray)
	{
		float sin_a = std::sin(current_angle);
		float cos_a = std::cos(current_angle);

		sin_a = sin_a ? sin_a : 0.000001;
		cos_a = cos_a ? cos_a : 0.000001;

		// Bresenham's line algorithm
		//for verticals
		
		int x, dx, y, dy;
		int yv, xh;
		float depth_vertical, depth_horizontal;
		TEXTURE texture_vertical, texture_horizontal;
		if (cos_a >= 0)
		{
			x = mapped_pos.x + AppConfig::tile;
			dx = 1;
		}
		else 
		{
			x = mapped_pos.x;
			dx = -1;
		}
		for (int i = 0; i < AppConfig::windows_rect.w; i += AppConfig::tile)
		{
			depth_vertical = (x - player_pos_x) / cos_a;
			yv = (int)(player_pos_y + depth_vertical * sin_a);
			SDL_Point tile_vertical = mapping({x + dx, yv});
			if (map->worldMapContains(tile_vertical))
			{
				texture_vertical = map->get(tile_vertical);
				break;
			}
			x += dx * AppConfig::tile;
		}	

		// for horizontals
		if (sin_a >= 0)
		{
			y = mapped_pos.y + AppConfig::tile;
			dy = 1;
		}
		else 
		{
			y = mapped_pos.y;
			dy = -1;
		}
		for (int i = 0; i < AppConfig::windows_rect.h; i += AppConfig::tile)
		{
			depth_horizontal = int(y - player_pos_y) / sin_a;
			xh = (int)(player_pos_x + depth_horizontal * cos_a);
			SDL_Point tile_horizontal = mapping({xh, y + dy});
			if (map->worldMapContains(tile_horizontal))
			{
				texture_horizontal = map->get(tile_horizontal);
				break;
			}
			y += dy * AppConfig::tile;
		}	

		// -> projection
		//float depth = (depth_vertical < depth_horizontal) ? depth_vertical : depth_horizontal;
		float depth;
		int offset;
		TEXTURE texture;
		if (depth_vertical < depth_horizontal)
		{
			depth = depth_vertical;
			offset = yv;
			texture = texture_vertical;
		}
		else 
		{
			depth = depth_horizontal;
			offset = xh;
			texture = texture_horizontal;
		}
		offset = offset % AppConfig::tile;
		depth = depth * std::cos(player_angle - current_angle);
		depth = std::max(depth, (float)0.00001);
	    float projection_height = std::min((AppConfig::projection_coeff / depth), 3.f * AppConfig::windows_rect.h);
	    SDL_Rect rect_from;
	    rect_from.x = offset * AppConfig::texture_scale;
	    rect_from.y = 0;
	    rect_from.w = AppConfig::texture_scale;
	    rect_from.h = AppConfig::texture_height;
	    SDL_Rect rect_to;
	    rect_to.x = nray * AppConfig::scale;
	    rect_to.y = AppConfig::half_height - std::round(projection_height / 2.0);
	    rect_to.w = AppConfig::scale;
	    rect_to.h = projection_height;
	    if (texture < TEXTURE::_) texture_manager->draw_texture(renderer, texture, rect_from, rect_to);
	    current_angle += AppConfig::delta_angle;
    }
}