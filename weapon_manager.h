#ifndef WEAPON_H
#define WEAPON_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include <string>

enum class WeaponType
{
	Minigan,
	Count
};

class WeaponManager
{
public:
	static WeaponManager* get(SDL_Renderer *renderer);
	static void destroy();
	void drawWeapon(SDL_Renderer *renderer, WeaponType type, SDL_Rect from, SDL_Rect to);
private:
	static WeaponManager* instance;
	WeaponManager(SDL_Renderer *renderer);
	~WeaponManager();
	static std::vector<std::string> pathes_to_weapons;
	std::vector<SDL_Texture*> weapons;
};

#endif