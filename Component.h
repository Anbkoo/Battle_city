#pragma once
#include "Container.h"
#include "Vector2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Element.h"
#include "Map.h"

class Component : public Container_Component {
public:
	Vector2d pos, speed;

	int const_speed, height, width;
	char sight = 'D';

	Component() {
		pos.Zero();
	}
	Component(int width, int height, int _speed, int x, int y)
		: width{ width / 20 },
		height{ height / 20 },
		const_speed(_speed){

		pos.x = x;
		pos.y = y;
	}

	void init() override {
		speed.Zero();
	}

	void update() override {
		pos.x += speed.x * const_speed;
		pos.y += speed.y * const_speed;
	}

	std::pair <int, int> getPosition() {
		return  std::make_pair(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
	
	std::pair <int, int> getSize() {
		return  std::make_pair(static_cast<int>(width), static_cast<int>(height));
	}

	char get_sight_tank() {
		return sight;
	}

	void set_sight(char _sight) {
		sight = _sight;
	}
};

class Collision {
public:
	static bool check_coll(std::pair <int, int> size_el, int pos_x, int pos_y, const std::vector<std::vector<int>>& element_map, char sight, int _WINDOW_WIDTH, int _WINDOW_HEIGHT);
};