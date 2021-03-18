#include "appconfig.h"
#include <cmath>

SDL_Rect AppConfig::windows_rect = {0, 0, 1200, 700};
int AppConfig::half_height = std::floor(AppConfig::windows_rect.h / 2);
int AppConfig::half_width = std::floor(AppConfig::windows_rect.w / 2);
int AppConfig::fps = 60;
int AppConfig::tile = 100;

int AppConfig::map_scale = 5;
int AppConfig::map_tile = std::floor(AppConfig::tile / AppConfig::map_scale);
SDL_Point AppConfig::map_pos = {0, 0};

float AppConfig::fov = M_PI / 3;
float AppConfig::half_fov = AppConfig::fov / 2;
int AppConfig::num_rays = 600;
int AppConfig::max_depth = 800;
float AppConfig::delta_angle = AppConfig::fov / AppConfig::num_rays;
float AppConfig::distantion = AppConfig::num_rays / (2 * std::tan(AppConfig::half_fov));
float AppConfig::projection_coeff = AppConfig::distantion * AppConfig::tile;
int AppConfig::scale = std::floor(AppConfig::windows_rect.w / AppConfig::num_rays);

Vector2f AppConfig::player_pos = {(float)AppConfig::half_width, (float)AppConfig::half_height};
float AppConfig::player_angle = 0;
float AppConfig::player_speed = 2.0;
float AppConfig::player_angle_speed = 0.02;

int AppConfig::texture_width = 1024;
int AppConfig::texture_height = 1024;
int AppConfig::texture_scale = std::floor(AppConfig::texture_width / AppConfig::tile);