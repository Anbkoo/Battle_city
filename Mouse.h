#pragma once
#include "Container.h"
#include "Component.h"
#include "Framework.h"
#include "Bullet.h"

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class Mouse : public Container_Component {
public:
	Mouse() = default;
	Mouse(int _WINDOW_WIDTH, int _WINDOW_HEIGHT, std::vector<Bullet> *_vectorBullets)
		:HEIGHT(_WINDOW_HEIGHT),
		WIDTH(_WINDOW_WIDTH),
		vectorBullets(_vectorBullets) {}

	void update() override {
		if (Framework::event.type == SDL_MOUSEBUTTONDOWN) {
			if (Framework::event.button.button == SDL_BUTTON_LEFT) {
				component = &entity->getComponent<Component>(); 
				int id = 0;
				auto it = std::find_if(vectorBullets->begin(), vectorBullets->end(), [id](Bullet obj) {
					return obj.get_tank_id() == id; });
				if (it == vectorBullets->end()) {
					Bullet bullet = Bullet({
					component->getPosition().first,
					component->getPosition().second,
					component->getSize().first,
					component->getSize().second, 3,
					component->get_sight_tank(),
					0});
					vectorBullets->push_back(bullet);
				}
			}
		}
	}

	int return_bullet() {
		return count_bullet++;
	}

	std::vector<Bullet> *vectorBullets;
private:
	int WIDTH, HEIGHT, count_bullet = 0;
	Component *component;
};