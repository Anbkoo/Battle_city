#include "Map.h"
#include "Framework.h"
#include "Element.h"

Map::Map(int WINDOW_WIDTH, int WINDOW_HEIGHT)
	:water{ Element::createElement("data/water.png") },
	wall{ Element::createElement("data/wall.png") },
	trees{ Element::createElement("data/tree.png") },
	ice{ Element::createElement("data/ice.png") },
	bricks{ Element::createElement("data/bricks.png") },
	borders{ Element::createElement("data/border.png") },
	prize{ Element::createElement("data/prize.png") }
{
	WIDTH = WINDOW_WIDTH;
	HEIGHT = WINDOW_HEIGHT;
	createMap();
	src_capacity.x = src_capacity.y = 0;
	src_capacity.w = dest_capacity.w = WIDTH / 16;
	src_capacity.h = dest_capacity.h = HEIGHT / 16;

	dest_capacity.x = dest_capacity.y = 0;

}

Map::~Map() {
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(trees);
	SDL_DestroyTexture(ice);
	SDL_DestroyTexture(bricks);
	SDL_DestroyTexture(borders);
	SDL_DestroyTexture(prize);
}

void Map::createMap() {
	std::ifstream map(path);
	if (map.fail()) {
		std::cout << "Unable to load map file!\n" << std::endl;
		exit(0);
	}

	int tileType = -1;
	std::vector<int> temp;

	while (!map.eof()) {
		char next = map.get();
		if (next == '\n') {
			element.push_back(temp);
			temp.clear();
			continue;
		}
		temp.push_back(atoi(&next));
	}
	if (!temp.empty()) {
		element.push_back(temp);
		temp.clear();
	}
	map.close();
}

void Map::drawMap() {
	TYPE type_of_background_element;

	for (size_t i = 0; i < element.size(); i++) {
		for (size_t j = 0; j < element[i].size(); j++) {
			type_of_background_element = static_cast<TYPE>(element[i][j]);
			dest_capacity.x = dest_capacity.w * j;
			dest_capacity.y = dest_capacity.h * i;

			switch (type_of_background_element) {
			case TYPE::TILE_BRICKS:
				Element::drawElement(bricks, src_capacity, dest_capacity, NULL);
				break;
			case TYPE::TILE_ICE:
				Element::drawElement(ice, src_capacity, dest_capacity, NULL);
				break;
			case TYPE::TILE_TREES:
				Element::drawElement(trees, src_capacity, dest_capacity, NULL);
				break;
			case TYPE::TILE_WALL:
				Element::drawElement(wall, src_capacity, dest_capacity, NULL);
				break;
			case TYPE::TILE_WATER:
				Element::drawElement(water, src_capacity, dest_capacity, NULL);
				break;
			case TYPE::BORDER:
				Element::drawElement(borders, src_capacity, dest_capacity, NULL);
				break;
			case TYPE::PRIZE:
				Element::drawElement(prize, src_capacity, dest_capacity, NULL);
				break;
			default:
				break;
			}
		}
	}
}