#ifndef APPCONFIG_H
#define APPCONFIG_H
#include <SDL2/SDL_rect.h>
#include "vector2f.h"

class AppConfig
{
public:
	static SDL_Rect windows_rect;
	static int half_height;
	static int half_width;
	static int fps;
	static int tile;

	// minimap settings
	static int map_scale;
	static int map_tile;
	static SDL_Point map_pos;

	// screen projection settings
	static float fov;
	static float half_fov;
	static int num_rays;
	static int max_depth;
	static float delta_angle;
	static float distantion;
	static float projection_coeff;
	static int scale;

	// player settings
	static Vector2f player_pos;
	static float player_angle;
	static float player_speed;
	static float player_angle_speed;

	// texture settings
	static int texture_width;
	static int texture_height;
	static int texture_scale;
};

#endif