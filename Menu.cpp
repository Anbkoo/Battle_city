#include "Menu.h"
#include "SDL_ttf.h"
#include "Framework.h"
#include "Element.h"

StartMenu::StartMenu(int WINDOW_WIDTH, int WINDOW_HEIGHT)
	: width{ WINDOW_WIDTH },
	height{ WINDOW_HEIGHT } {
	texture = Element::createElement("data/start.png");
	dest_capacity.x = width / 6;
	dest_capacity.y = dest_capacity.h = height / 8;
	dest_capacity.w = width / 1.5;
	dest_capacity.h = height / 3;

};

StartMenu::~StartMenu() {
	SDL_DestroyTexture(texture);
	TTF_Quit();
}

void StartMenu::Render() {
	SDL_RenderClear(Framework::renderer);
	SDL_RenderCopy(Framework::renderer, texture, NULL, &dest_capacity);
	for (size_t i = 0; i < number_menu; i++)
		SDL_RenderCopy(Framework::renderer, text[i], NULL, &pos[i]);
	SDL_RenderPresent(Framework::renderer);
}

SDL_Texture* StartMenu::Load_Font(std::string font_path, int font_size, const std::string &message, const SDL_Color& color) {
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font)
		std::cout << "TTF_Font Error: " << TTF_GetError() << std::endl;

	auto text = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!text) 
		std::cout << "TTF_Render Error: " << SDL_GetError() << std::endl;

	auto text_texture = SDL_CreateTextureFromSurface(Framework::renderer, text);
	if (!text_texture)
		std::cout << "Text Texture Error: " << SDL_GetError() << std::endl;

	SDL_FreeSurface(text);
	return text_texture;
}

int StartMenu::showMenu(SDL_Window* window, SDL_Surface* screen) {
	SDL_Event event;
	SDL_SetRenderDrawColor(Framework::renderer, 0, 0, 0, 255);
	std::string font_path = "data/IndieFlower-Regular.ttf";
	const char*	labels_menu[number_menu] = { "1 PLAYER", "2 PLAYERS", "INSTRUCTIONS", "EXIT" };
	SDL_Color white_color = { 255, 255, 255 }, red_color = { 255, 0, 0 };

	for (size_t i = 0; i < number_menu; i++) {
		text[i] = Load_Font(font_path, menu_font_size, labels_menu[i], white_color);

		pos[i].y = dest_capacity.y + dest_capacity.h + i * (menu_font_size + 10);
		pos[i].x = dest_capacity.x + dest_capacity.w / 3;
		pos[i].w = width / 6;
		pos[i].h = 30 ;

		SDL_QueryTexture(text[i], nullptr, nullptr, &pos[i].w, &pos[i].h);
	}

	int pos_cursor_x, pos_cursor_y;
	while (true) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEMOTION:
				pos_cursor_x = event.motion.x;
				pos_cursor_y = event.motion.y;

				for (size_t i = 0; i < number_menu; i++) {
					if (pos_cursor_x >= pos[i].x && pos_cursor_x <= pos[i].x + pos[i].w
						&& pos_cursor_y >= pos[i].y && pos_cursor_y <= pos[i].y + pos[i].h)
						text[i] = Load_Font(font_path, menu_font_size, labels_menu[i], red_color);
					else
						text[i] = Load_Font(font_path, menu_font_size, labels_menu[i], white_color);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				pos_cursor_x = event.motion.x;
				pos_cursor_y = event.motion.y;
				for (size_t i = 0; i < number_menu; i++) {
					if (pos_cursor_x >= pos[i].x && pos_cursor_x <= pos[i].x + pos[i].w
						&& pos_cursor_y >= pos[i].y && pos_cursor_y <= pos[i].y + pos[i].h)
						return i;
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					exit(0);
				break;
			default:
				break;
			}
		}
		Render();
	}
	return 0;
}


