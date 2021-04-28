#pragma once
#include "Container.h"
#include "Component.h"
#include "Framework.h"
#include <iostream>
#include "Map.h"

class KeyBoard : public Container_Component {
public:
	KeyBoard() = default;
	KeyBoard(Map *_map, int _WINDOW_WIDTH, int _WINDOW_HEIGHT)
		:WINDOW_HEIGHT(_WINDOW_HEIGHT),
		WINDOW_WIDTH(_WINDOW_WIDTH) {
		element_map = _map->get_element_of_map();
		size_el = _map->getSize(_map->water);
	};

	void init() override {
		component = &entity->getComponent<Component>();
		turn_element = &entity->getComponent<Sprite>();
	}

	void update() override {
		if (Framework::event.type == SDL_KEYDOWN)
			onKeyPressed();
		if (Framework::event.type == SDL_KEYUP)
			onKeyReleased();
	}

	void onKeyPressed() {
		switch (Framework::event.key.keysym.sym) {
		case SDLK_UP:
			changed_size('U');
			component->set_sight('U');
			if (Collision::check_coll(component->getSize(),component->getPosition().first, component->getPosition().second - 1, 
				element_map, component->get_sight_tank(), WINDOW_WIDTH, WINDOW_HEIGHT))
				component->speed.y = -1;
			else
				zero_speed();
			turn_element->angle = 180;
			break;
		case SDLK_LEFT:
			changed_size('L');
			component->set_sight('L');
			if (Collision::check_coll(component->getSize(), component->getPosition().first - 1, component->getPosition().second,
				element_map, component->get_sight_tank(), WINDOW_WIDTH, WINDOW_HEIGHT))
				component->speed.x = -1;
			else
				zero_speed();
			turn_element->angle = 90;
			break;
		case SDLK_RIGHT:
			changed_size('R');
			component->set_sight('R');
			if (Collision::check_coll(component->getSize(), component->getPosition().first + 1, component->getPosition().second,
				element_map, component->get_sight_tank(), WINDOW_WIDTH, WINDOW_HEIGHT))
				component->speed.x = 1;
			else
				zero_speed();
			turn_element->angle = -90;
			break;
		case SDLK_DOWN:
			changed_size('D');
			component->set_sight('D');
			if (Collision::check_coll(component->getSize(), component->getPosition().first, component->getPosition().second + 1,
				element_map, component->get_sight_tank(), WINDOW_WIDTH, WINDOW_HEIGHT))
				component->speed.y = 1;
			else
				zero_speed();
			turn_element->angle = 0;
			break;
		default:
			break;
		}
	}

	void changed_size(char new_sight) {
		if ((component->get_sight_tank() == 'D' || component->get_sight_tank() == 'U') && (new_sight == 'R' || new_sight == 'L'))
			turn_element->changed_size();
		else if ((component->get_sight_tank() == 'R' || component->get_sight_tank() == 'L') && (new_sight == 'U' || new_sight == 'D'))
			turn_element->changed_size();
	}

	void zero_speed() {
		component->speed.y = 0;
		component->speed.x = 0;
	}

	void onKeyReleased() {
		switch (Framework::event.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_RIGHT:
		case SDLK_LEFT:
		case SDLK_DOWN:
			zero_speed();
			break;
		case SDLK_ESCAPE:
			Framework::running = false;
			break;
		default:
			break;
		}
	}

private:
	Component *component;
	Sprite *turn_element;
	std::vector<std::vector<int>> element_map;
	int WINDOW_WIDTH, WINDOW_HEIGHT;
	std::pair <int, int> size_el;
};