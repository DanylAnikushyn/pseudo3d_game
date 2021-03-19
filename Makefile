CC=g++

all: pseudo3d_game

pseudo3d_game: main.cpp appconfig.h appconfig.cpp raycasting.h raycasting.cpp player.h player.cpp map.h map.cpp textures_manager.cpp textures_manager.h weapon_manager.cpp weapon_manager.h interface.cpp interface.h
	$(CC) main.cpp appconfig.h appconfig.cpp raycasting.h raycasting.cpp player.h player.cpp map.h map.cpp textures_manager.cpp textures_manager.h weapon_manager.cpp weapon_manager.h interface.cpp interface.h -o bin/main -lSDL2 -lSDL2_image -lSDL2_ttf
