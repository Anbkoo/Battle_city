#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Framework.h"
#include "Element.h"
#include <sstream>

// TYPE OF MAP ELEMENTS
enum class TYPE {
	EMPTY,
	TILE_BRICKS,
	TILE_ICE,
	TILE_TREES,
	TILE_WALL,
	TILE_WATER,
	BORDER,
	PRIZE,
	TANK,
	ENEMY_TANK,
	COUNT
};

class Map {
public:
	Map(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	~Map();

	void createMap();
	void drawMap();

	std::pair <int, int> getSize(SDL_Texture *texture) {
		SDL_Point size;
		SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
		return std::make_pair(size.x, size.y);
	}

	std::vector<std::vector<int>> get_element_of_map() {
		return element;
	}

	SDL_Texture *water, *wall, *trees, *ice, *bricks, *borders, *prize;
private:
	SDL_Rect src_capacity, dest_capacity;
	
	std::string path = "leve1.map";
	std::vector<std::vector<int>> element;
	int WIDTH, HEIGHT;
};