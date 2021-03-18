#ifndef INTERFACE_H
#define INTERFACE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "appconfig.h"

class Interface
{
public:
	static Interface* get();
	static void destroy();
	void displayFPS(SDL_Renderer *renderer, int FPS);

	Interface(Interface &other) = delete;
	void operator=(const Interface &) = delete;
private:
	Interface();
	~Interface();
	static Interface* instance;
	TTF_Font* font;
};

#endif