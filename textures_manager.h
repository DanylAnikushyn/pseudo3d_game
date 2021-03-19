#ifndef SPRITES_H
#define SPRITES_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include "map.h" 

class TexturesManager
{
public:
	static TexturesManager *get(SDL_Renderer *renderer);
	static void destroy();
	void draw_texture(SDL_Renderer *renderer, TEXTURE type, SDL_Rect rect_from, SDL_Rect rect_to) const;
	void draw_background(SDL_Renderer *renderer, float angle) const;
private:
	TexturesManager(SDL_Renderer *renderer);
	~TexturesManager();
	static TexturesManager *instance;
	static std::vector<std::string> pathes_to_textures;
	std::vector<SDL_Texture*> textures;
};

#endif