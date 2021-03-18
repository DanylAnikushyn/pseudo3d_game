#include "textures_manager.h"
#include "appconfig.h"
#include <cmath>
#include <iostream>


std::vector<std::string> TexturesManager::pathes_to_textures = {
	"textures/texture1.jpg",
	"textures/d_sky.png"
};

TexturesManager* TexturesManager::instance = nullptr;

TexturesManager::TexturesManager(SDL_Renderer* renderer)
{
	for (int i = 0; i < pathes_to_textures.size(); ++i)
	{
		textures.push_back(IMG_LoadTexture(renderer, pathes_to_textures.at(i).c_str())); // can be error, nullptr will be pushed into vector
	}
}

TexturesManager::~TexturesManager()
{
	for (int i = 0; i < pathes_to_textures.size(); ++i)
	{
		SDL_DestroyTexture(textures.at(i));
	}
}

TexturesManager* TexturesManager::get(SDL_Renderer *renderer)
{
	if (!instance)
	{
		instance = new TexturesManager(renderer);
	}
	return instance;
}

void TexturesManager::destroy()
{
	delete instance;
	instance = nullptr;
}

void TexturesManager::draw_skybox(SDL_Renderer *renderer, float angle)
{
	int sky_offset = (int)(-10 * angle * (180.f / M_PI)) % AppConfig::windows_rect.w;
	SDL_Rect rect_from;
	rect_from.h = AppConfig::half_height;
	rect_from.y = 0;
	SDL_Rect rect_to;
	rect_to.h = AppConfig::half_height;
	rect_to.y = 0;

	rect_from.w = AppConfig::windows_rect.w + sky_offset;
	rect_from.x = -sky_offset;
	rect_to.w = AppConfig::windows_rect.w + sky_offset;
	rect_to.x = 0;
	SDL_RenderCopy(renderer, textures.at((int)S), &rect_from, &rect_to);
	rect_from.w = -sky_offset;
	rect_from.x = 0;
	rect_to.w = -sky_offset;		
	rect_to.x = AppConfig::windows_rect.w + sky_offset;
	SDL_RenderCopy(renderer, textures.at((int)S), &rect_from, &rect_to);
}

void TexturesManager::draw_texture(SDL_Renderer *renderer, TEXTURE type, SDL_Rect rect_from, SDL_Rect rect_to)
{
	SDL_RenderCopy(renderer, textures.at((int)type), &rect_from, &rect_to);
}