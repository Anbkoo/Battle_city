#pragma once
#include "Element.h"
#include "SDL.h"

struct Bullet {
	Bullet(int _x_pos, int _y_pos, int _width, int _height, int _speed, char _sight, int _tank_id)
		:pos_x(_x_pos),
		pos_y(_y_pos),
		speed(_speed) {
		
		element = Element::createElement(path.c_str());

		dest_capacity.w = src_capacity.w = _width;
		dest_capacity.h = src_capacity.h = _height;

		src_capacity.x = src_capacity.y = 0;
		dest_capacity.x = _x_pos;
		dest_capacity.y = _y_pos;
		tank_id = _tank_id;

		switch (_sight) {
		case 'D':
			angle = 180;
			dest_capacity.y = _y_pos + _height / 2;
			y_speed = speed;
			break;
		case 'U':
			angle = 0;
			dest_capacity.y = _y_pos - _height / 2;
			y_speed = -speed;
			break;
		case 'R':
			angle = 90;
			dest_capacity.x = _x_pos + _width / 2;
			x_speed = speed;
			break;
		case 'L':
			angle = -90;
			dest_capacity.x = _x_pos - _width / 2;
			x_speed = -speed;
			break;
		default:
			break;
		}
	}

	int get_tank_id(){
		return  tank_id;
	}

	SDL_Texture* getTexture() {
		return element;
	}

	std::pair <int, int> getPosition() {
		return  { pos_x, pos_y };
	}

	SDL_Rect get_dest_rec() {
		return dest_capacity;
	}

	SDL_Rect get_src_rec() {
		return src_capacity;
	}

	void move() {
		dest_capacity.x += x_speed;
		dest_capacity.y += y_speed;

		pos_x = dest_capacity.x;
		pos_y = dest_capacity.y;
	}

	char get_sight_enemy() {
		return  sight_enemy;
	}

	void set_sight_enemy(char _sight_enemy) {
		sight_enemy = _sight_enemy;
	}

	void set_angle(int _angle) {
		angle = _angle;
	}

	int get_angle() {
		return angle;
	}


private:
	int  pos_x, pos_y; //Position of enemy
	int speed = 0, angle = 0;
	int x_speed = 0, y_speed = 0;
	int tank_id;
	SDL_Texture* element = nullptr;
	Component *component;
	char sight_enemy = 'D';
	std::string path = "data/bullet.png";
	SDL_Rect src_capacity, dest_capacity;
};