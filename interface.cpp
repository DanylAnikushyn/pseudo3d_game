#include "interface.h"

Interface* Interface::instance = nullptr;

Interface::Interface()
{
	font = TTF_OpenFont("fonts/mincho.ttf", 24); 
	if (font == nullptr)
	{
		std::cerr << "TTF_OpenFont" << std::endl;
	}
}

Interface::~Interface()
{
	TTF_CloseFont(font);
}

Interface* Interface::get()
{
	if (!instance)
	{
		instance = new Interface();
	}
	return instance;
}

void Interface::destroy()
{
	delete instance;
	instance = nullptr;
}

void Interface::displayFPS(SDL_Renderer *renderer, int FPS)
{
	SDL_Color White = {255, 255, 255};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, std::to_string(FPS).c_str(), White);
	if (surfaceMessage == nullptr)
	{
		std::cerr << "TTF_RenderText_Solid" << std::endl;
	} 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
	if (Message == nullptr)
	{
		std::cerr << "SDL_CreateTextureFromSurface" << std::endl;
	} 
	SDL_Rect Message_rect; 
	Message_rect.x = AppConfig::windows_rect.w - 90;   
	Message_rect.y = 10; 
	Message_rect.w = 50; 
	Message_rect.h = 50; 
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}