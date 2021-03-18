#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL2/SDL.h>
#include <map>

enum TEXTURE
{
	W,
	S,
	_,
};

struct SDLPointCompare
{
	bool operator() (const SDL_Point& lhs, const SDL_Point& rhs)
	{
		return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
	}
};

class Map
{
public:
	Map();
	bool worldMapContains(SDL_Point point);
	bool collisionDetected(SDL_Point point);
	void drawMiniMap(SDL_Renderer *renderer, SDL_Point player_pos, float player_angle);
	TEXTURE get(SDL_Point point);
	std::vector<SDL_Point> mini_map;
private:
	std::map<SDL_Point, TEXTURE, SDLPointCompare> world_map;
};

#endif