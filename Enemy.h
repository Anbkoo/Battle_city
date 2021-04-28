#pragma once
#include "Element.h"
#include "SDL.h"

struct Enemy {
	Enemy(int _pos_x, int _pos_y, int WIDTH,  int HEIGHT, int _speed, int i, int _health)
		:pos_x (_pos_x),
		pos_y(_pos_y),
		speed(_speed),
		health(_health){
		std::string temp = "data/tank" + std::to_string(i) + ".png";
		m_enemy = Element::createElement(temp.c_str());

		dest_capacity.w = src_capacity.w = WIDTH / 20;
		dest_capacity.h = src_capacity.h = HEIGHT / 20;

		src_capacity.x = src_capacity.y = 0;
		dest_capacity.x = _pos_x;
		dest_capacity.y = _pos_y;

	}

	SDL_Texture* getEnemyTexture() { 
		return m_enemy; 
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

	void setPosition(int _pos_x, int _pos_y) {
		pos_x = _pos_x;
		pos_y = _pos_y;

		dest_capacity.x = pos_x;
		dest_capacity.y = pos_y;
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

	int get_speed() {
		return speed;
	}

	void changed_size_dest() {
		int temp = dest_capacity.w;
		dest_capacity.w = src_capacity.w = dest_capacity.h;
		dest_capacity.h = src_capacity.h = temp;
	}

	static void changed_size(char new_sight, Enemy& enemy) {
		if ((enemy.get_sight_enemy() == 'D' || enemy.get_sight_enemy() == 'U') && (new_sight == 'R' || new_sight == 'L'))
			enemy.changed_size_dest();
		else if ((enemy.get_sight_enemy() == 'R' || enemy.get_sight_enemy() == 'L') && (new_sight == 'U' || new_sight == 'D'))
			enemy.changed_size_dest();
	}

	void template_function(char new_sight, int angle, int x, int y, Enemy& enemy) {
		enemy.changed_size(new_sight, enemy);
		enemy.set_sight_enemy(new_sight);
		enemy.set_angle(angle);
		enemy.setPosition(enemy.getPosition().first + x, enemy.getPosition().second + y);
	}

	static bool enemies_down(Component& component, Enemy& enemy, const std::vector<std::vector<int>>& element, const int& WIDTH, const int& HEIGHT) {
		if (Collision::check_coll(component.getSize(), enemy.getPosition().first + enemy.get_speed(),
			enemy.getPosition().second, element, enemy.get_sight_enemy(), WIDTH, HEIGHT)) {
			enemy.template_function('D', 0, 1, 0, enemy);
			return true;
		}
		return false;
	}

	static bool enemies_up(Component& component, Enemy& enemy, const std::vector<std::vector<int>>& element, const int& WIDTH, const int& HEIGHT) {
		if (Collision::check_coll(component.getSize(), enemy.getPosition().first - enemy.get_speed(),
			enemy.getPosition().second, element, enemy.get_sight_enemy(), WIDTH, HEIGHT)) {
			enemy.template_function('U', 180, -1, 0, enemy);
			return true;
		}
		return false;
	}

	static bool enemies_right(Component& component, Enemy& enemy, const std::vector<std::vector<int>>& element, const int& WIDTH, const int& HEIGHT) {
		if (Collision::check_coll(component.getSize(), enemy.getPosition().first,
			enemy.getPosition().second + enemy.get_speed(), element, enemy.get_sight_enemy(), WIDTH, HEIGHT)) {
			enemy.template_function('R', -90, 0, 1, enemy);
			return true;
		}
		return false;
	}

	static bool enemies_left(Component& component, Enemy& enemy, const std::vector<std::vector<int>>& element, const int& WIDTH, const int& HEIGHT) {
		if (Collision::check_coll(component.getSize(), enemy.getPosition().first - enemy.get_speed(),
			enemy.getPosition().second, element, enemy.get_sight_enemy(), WIDTH, HEIGHT)) {
			enemy.template_function('L', 90, 0, -1, enemy);
			return true;
		}
		return false;
	}



private:
	int health;
	int  pos_x, pos_y;//Position of enemy
	int speed = 0, angle = 0;
	SDL_Texture* m_enemy = nullptr;
	Component *component;
	char sight_enemy = 'D';
	SDL_Rect src_capacity, dest_capacity;
};