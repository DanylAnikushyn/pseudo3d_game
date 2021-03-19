#include "weapon_manager.h"
#include "appconfig.h"

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


void WeaponManager::drawWeapon(SDL_Renderer* renderer, WeaponType type) const
{
	SDL_Rect from;
	from.w = 1157; from.h = 495; from.x = 0; from.y = 0;
	SDL_Rect to;
	to.w = 900; to.h = 400; to.x = 300; to.y = AppConfig::windows_rect.h - to.h + 100; 
	SDL_RenderCopy(renderer, weapons.at((int)type), &from, &to);
}