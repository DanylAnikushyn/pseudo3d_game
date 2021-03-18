#include "weapon_manager.h"
#include <iostream>

std::vector<std::string> WeaponManager::pathes_to_weapons = {
	"textures/weapon.png"
};

WeaponManager* WeaponManager::instance = nullptr;

WeaponManager::WeaponManager(SDL_Renderer* renderer)
{
	for (int i = 0; i < pathes_to_weapons.size(); ++i)
	{
		weapons.push_back(IMG_LoadTexture(renderer, pathes_to_weapons.at(i).c_str())); // can be error, nullptr will be pushed into vector
	}
}

WeaponManager::~WeaponManager()
{
	for (int i = 0; i < pathes_to_weapons.size(); ++i)
	{
		SDL_DestroyTexture(weapons.at(i));
	}
}

WeaponManager* WeaponManager::get(SDL_Renderer *renderer)
{
	if (!instance)
	{
		instance = new WeaponManager(renderer);
	}
	return instance;
}

void WeaponManager::destroy()
{
	delete instance;
	instance = nullptr;
}


void WeaponManager::drawWeapon(SDL_Renderer* renderer, WeaponType type, SDL_Rect from, SDL_Rect to)
{
	SDL_RenderCopy(renderer, weapons.at((int)type), &from, &to);
}