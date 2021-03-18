#include "map.h"
#include "appconfig.h"
#include <cmath>

Map::Map()
{
	std::vector<std::vector<TEXTURE>> map = {
		{W, W, W, W, W, W, W, W, W, W, W, W},
		{W, _, _, _, _, _, _, W, _, _, _, W},
		{W, _, _, W, W, W, _, _, _, W, _, W},
		{W, _, _, _, _, W, _, _, W, W, _, W},
		{W, _, _, W, _, _, _, _, W, _, _, W},
		{W, _, _, W, _, _, _, W, W, W, _, W},
		{W, _, _, _, _, W, _, _, _, _, _, W},
		{W, W, W, W, W, W, W, W, W, W, W, W}
	};
	for (int row = 0; row < map.size(); ++row)
	{
		for(int el = 0; el < map.at(row).size(); ++el)
		{
			switch (map.at(row).at(el))
			{
				case W:
					world_map.insert({{el * AppConfig::tile, row * AppConfig::tile}, W});
					mini_map.push_back({el * AppConfig::map_tile, row * AppConfig::map_tile});
					break;
				case _:
					break;
			}
		}
	}
}

bool Map::worldMapContains(SDL_Point point)
{
	for (auto pair : world_map)
	{
		if (pair.first.x == point.x && pair.first.y == point.y)
		{
			return true;
		}
	}
	return false;
}

bool Map::collisionDetected(SDL_Point point)
{
	for (auto p : world_map)
	{
		if (p.first.x <= point.x && point.x <= p.first.x + AppConfig::tile &&
			p.first.y <= point.y && point.y <= p.first.y + AppConfig::tile)
			return true;
	}
	return false;
}

void Map::drawMiniMap(SDL_Renderer *renderer, SDL_Point player_pos, float player_angle)
{
	SDL_Rect minimap_rect;
	minimap_rect.w = std::floor(AppConfig::windows_rect.w / AppConfig::map_scale);
	minimap_rect.h = std::floor(AppConfig::windows_rect.h / AppConfig::map_scale);
	minimap_rect.x = AppConfig::map_pos.x;
	minimap_rect.y = AppConfig::map_pos.y;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &minimap_rect);
	SDL_SetRenderDrawColor(renderer, 1, 50, 32, 255);
	SDL_Rect tile_rect;
	tile_rect.w = AppConfig::map_tile;
	tile_rect.h = AppConfig::map_tile;
	for (auto point : mini_map)
	{
		tile_rect.x = point.x + AppConfig::map_pos.x;
		tile_rect.y = point.y + AppConfig::map_pos.y;
		SDL_RenderFillRect(renderer, &tile_rect);
	}
	SDL_Rect player_rect;
	tile_rect.w = 8;
	tile_rect.h = 8;
	tile_rect.x = std::floor(player_pos.x / AppConfig::map_scale) - 4;
	tile_rect.y = std::floor(player_pos.y / AppConfig::map_scale) - 4;
	SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);
	SDL_RenderFillRect(renderer, &tile_rect);
	SDL_RenderDrawLine(renderer, std::floor(player_pos.x / AppConfig::map_scale), std::floor(player_pos.y / AppConfig::map_scale),
		std::floor(player_pos.x / AppConfig::map_scale) + std::cos(player_angle) * 12,
		std::floor(player_pos.y / AppConfig::map_scale) + std::sin(player_angle) * 12);
}

TEXTURE Map::get(SDL_Point point)
{
	return world_map[point];
}