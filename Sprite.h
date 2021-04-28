#pragma once
#include "Container.h"
#include "Framework.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Element.h"
#include <iostream>
#include <map>


#if defined(_WINDOWS)

#if defined(FRAMEWORK_PROJECT)
#define FRAMEWORK_API extern "C" __declspec(dllexport)
#else
#define FRAMEWORK_API extern "C" __declspec(dllimport)
#endif
#else
#define FRAMEWORK_API 
#endif

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

struct Animation {
	int index, frames, speed;
	Animation() {}
	Animation(int _index, int _frames, int _speed)
		:index(_index),
		frames(_frames),
		speed(_speed)
	{}

};

class Sprite : public Container_Component {
public:
	FRAMEWORK_API Sprite() = default;
	FRAMEWORK_API Sprite(const char* path) {
		setTexture(path);
	}

	FRAMEWORK_API Sprite(const char* path, bool isAnimated) {
		animate = isAnimated;
		Animation _animation = Animation(0, 2, 100);

		animations.emplace("animate", _animation);
		Play("animate");
		setTexture(path);
	}

	FRAMEWORK_API ~Sprite() {
		destroySprite();
	}

	FRAMEWORK_API void destroySprite() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path) {
		texture = Element::createElement(path);
	}
	void init() {
		position = &entity->getComponent<Component>();

		src_box_capacity.x = src_box_capacity.y = 0;

		src_box_capacity.w = dest_box_capacity.w = position->width;
		src_box_capacity.h = dest_box_capacity.h = position->height;
	}

	void update() override {
		if (animate) {
			src_box_capacity.x = src_box_capacity.w * static_cast<int>((SDL_GetTicks() / animate_speed) % frames);
		}

		src_box_capacity.y = animate_index * position->height;

		dest_box_capacity.x = static_cast<int>(position->pos.x);
		dest_box_capacity.y = static_cast<int>(position->pos.y);
	}

	void draw() override {
		Element::drawElement(texture, src_box_capacity, dest_box_capacity, angle);
	}

	void Play(const char* name_of_animated) {
		frames = animations[name_of_animated].frames;
		animate_index = animations[name_of_animated].index;
		animate_speed = animations[name_of_animated].speed;
	}

	void changed_size() {
		int temp = dest_box_capacity.w;
		dest_box_capacity.w = src_box_capacity.w = dest_box_capacity.h;
		dest_box_capacity.h = src_box_capacity.h = temp;
	}

	int angle = 0;

private:
	Component *position;
	SDL_Texture* texture;
	SDL_Rect src_box_capacity, dest_box_capacity;

	bool animate = false;
	int frames = 0, animate_speed = 100, animate_index = 0;

	std::map<const char*, Animation> animations;
};
