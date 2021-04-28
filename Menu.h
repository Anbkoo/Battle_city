#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

class StartMenu {
public:
	StartMenu(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	~StartMenu();
	int showMenu(SDL_Window* window, SDL_Surface* screen);

	static SDL_Texture* Load_Font(std::string font_path, int font_size, const std::string &message, const SDL_Color& color);

	void Render();

private:
	int width, height;
	int menu_font_size = width / 15;
	static const int number_menu = 4;
	SDL_Texture * texture, *text[number_menu];
	SDL_Rect dest_capacity;
	SDL_Rect pos[number_menu];
};