#include "Element.h"
#include <iostream>

SDL_Texture* Element::createElement(const char* path) {
	SDL_Surface *temp = IMG_Load(path);
	if (!temp)
		printf("IMG_Load: %s\n", IMG_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(Framework::renderer, temp);
	SDL_FreeSurface(temp);

	return texture;
}

void Element::drawElement(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, double angle) {
	SDL_RenderCopyEx(Framework::renderer, texture, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}
