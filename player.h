#ifndef PLAYER_H

#define PLAYER_H

#include <SDL2/SDL.h>
#include "map.h"
#include "vector2f.h"

class Player
{
public:
	Player();
	Vector2f getPosition() const;
	float getAngle() const;
	void move(const Map *const map);
private:
	Vector2f pos;
	float angle;
};

#endif