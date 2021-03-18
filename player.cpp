#include "player.h"
#include "appconfig.h"
#include <iostream>
#include <cmath>

Player::Player()
{
  	pos = AppConfig::player_pos; 
    angle = AppConfig::player_angle; 
}

Vector2f Player::getPosition()
{
  	return pos;
}

float Player::getAngle()
{
  	return angle;
}

void Player::move(Map *map)
{
  	const Uint8 *keys = SDL_GetKeyboardState(NULL);
  	float sin_a = std::sin(angle);
  	float cos_a = std::cos(angle);
    float x = 0;
    float y = 0;
   	if (keys[SDL_SCANCODE_W]){
      	x = pos.x + AppConfig::player_speed * cos_a;
      	y = pos.y + AppConfig::player_speed * sin_a;
   	}
    if (keys[SDL_SCANCODE_S]){
       	x = pos.x - AppConfig::player_speed * cos_a;
      	y = pos.y - AppConfig::player_speed * sin_a;
   	}
   	if (keys[SDL_SCANCODE_A]){
      	x = pos.x + AppConfig::player_speed * sin_a;
      	y = pos.y - AppConfig::player_speed * cos_a;
   	}
    if (keys[SDL_SCANCODE_D]){
       	x = pos.x - AppConfig::player_speed * sin_a;
      	y = pos.y + AppConfig::player_speed * cos_a;
   	}
   	if (keys[SDL_SCANCODE_Q]){
   		angle -= AppConfig::player_angle_speed;
   	}
   	if (keys[SDL_SCANCODE_E]){
   		angle += AppConfig::player_angle_speed;
   	}
   	if (angle > M_PI * 2) angle -= M_PI * 2;
   	if (angle < 0) angle += M_PI * 2;

    if(!map->collisionDetected({(int)x, (int)y}))
    {
        pos.x = x;
        pos.y = y;
    }
}