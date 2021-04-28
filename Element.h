#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Framework.h"


class Element {
public:
	// without making object
	static SDL_Texture* createElement(const char* path);
	//FRAMEWORK_API Sprite* createSprite(const char* path);
	static void drawElement(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, double angle);
};

