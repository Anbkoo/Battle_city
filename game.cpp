#include "Framework.h"
#include "Element.h"
#include "Map.h"
#include "Container.h"
#include "Component.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Menu.h"
#include "Enemy.h"
#include <windows.h>

Map* map = nullptr;
StartMenu* menu = nullptr;

SDL_Renderer* Framework::renderer = nullptr;
SDL_Event Framework::event;

bool Framework::running = true;
const int enemy_numb = 4;
int enemy_health[enemy_numb] = {1, 1, 1, 4};

std::vector<Enemy> vector_enemies;
std::vector<Bullet> *vector_bullets;
std::vector<std::vector<int>> element;

Manager manager;
auto& player(manager.addEntity());

std::vector<std::pair <int, int>> set_vector_free_position(const std::vector<std::vector<int>>& element);
std::pair <int, int> take_free_spase(std::vector<std::pair <int, int>>&);
int return_game();
std::pair <int, int> parse_argv2(const std::string& str);
unsigned int getTickCount();
void show_help();
int run(Framework* Battle_Game);

class MyFramework : public Framework {

public:
	MyFramework() : WINDOW_WIDTH(320), WINDOW_HEIGHT(200), FullScreen(false) {}
	MyFramework(int width, int height, bool fullscreen)
		:WINDOW_WIDTH(width),
		WINDOW_HEIGHT(height),
		FullScreen(fullscreen) {}

	bool Init() override {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		if (TTF_Init() < 0) {
			std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
			return 1;
		}

		window = SDL_CreateWindow(GetTitle(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			FullScreen
		);

		SDL_GetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
		if (window == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer == nullptr) {
			std::cout << "Failed to create renderer: %s\n" << SDL_GetError() << std::endl;
			return 1;
		}

		screen = SDL_GetWindowSurface(window);
		if (screen == NULL) {
			SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
			exit(1);
		}

		back_menu();
		return true;
	}

	void back_menu() {
		menu = new StartMenu(WINDOW_WIDTH, WINDOW_HEIGHT);
		int i = menu->showMenu(window, screen);
		if (i == 3)
			running = false;
		start_game(i);
	}

	void addEnemy(std::vector<std::vector<int>> element, std::vector<std::pair <int, int>>& free_spase) {
		for (int i = 2; i < enemy_numb + 2; i++) {
			vector_enemies.push_back(Enemy({take_free_spase(free_spase).second * WINDOW_WIDTH / 16, 
				take_free_spase(free_spase).first * WINDOW_HEIGHT / 16 , WINDOW_WIDTH, WINDOW_HEIGHT, 3, i, enemy_health[i + 2]}));
		}
	}

	void moveEnemies(const std::vector<std::vector<int>>& element) {
		Component component = player.getComponent<Component>(); 
		for (auto &enemy : vector_enemies) {
			int random = rand() % 4 + 1;

			if (random == 1)
				enemy.enemies_right(component, enemy, element, WINDOW_WIDTH, WINDOW_HEIGHT);
			else if (random == 2)
				enemy.enemies_left(component, enemy, element, WINDOW_WIDTH, WINDOW_HEIGHT);
			else if (random == 3) 
					enemy.enemies_down(component, enemy, element, WINDOW_WIDTH, WINDOW_HEIGHT);
			else if (random == 4)
					enemy.enemies_up(component, enemy, element, WINDOW_WIDTH, WINDOW_HEIGHT);

		}
	}

	void moveBullets() {
		auto i = 0;
		for (auto &bullet : *vector_bullets) {
			std::pair<int, int> coord = bullet.getPosition();
			if (coord.first <= 0 || coord.second <= 0 || coord.first >= WINDOW_WIDTH || coord.second >= WINDOW_HEIGHT) {
				vector_bullets->erase(vector_bullets->begin() + i);
			}
			bullet.move();
			i++;
		}
	}

	void start_game(int i) {
		uint32_t frameStart;
		int frameTime;
		 
		if (i == 0) {
			map = new Map(WINDOW_WIDTH, WINDOW_HEIGHT);
			element = map->get_element_of_map();
			std::vector<std::pair <int, int>> free_spase = set_vector_free_position(element);

			player.addComponent<Component>(WINDOW_WIDTH, WINDOW_HEIGHT, 3, take_free_spase(free_spase).second * WINDOW_WIDTH / 16, take_free_spase(free_spase).first * WINDOW_HEIGHT / 16);
			vector_bullets = new std::vector<Bullet>();
			player.addComponent<Sprite>("data/tankD.png", false);
			player.addComponent<Mouse>(WINDOW_WIDTH, WINDOW_HEIGHT, vector_bullets);
			player.addComponent<KeyBoard>(map, WINDOW_WIDTH, WINDOW_HEIGHT);
			player.addGroup(groupPlayers);

			addEnemy(element, free_spase);

			while (running) {
				frameStart = getTickCount();

				HandleWindowEvent();
				Update();
				Render_Player();

				frameTime = getTickCount() - frameStart;

				if (frameDelay > frameTime)
					SDL_Delay(frameDelay - frameTime);
			}
		}
		else {
			std::string font_path = "data/IndieFlower-Regular.ttf", message = "In the next series";
			SDL_Color white_color = { 255, 255, 255 };
			SDL_Texture *texture = StartMenu::Load_Font(font_path, 50, message, white_color);
			SDL_QueryTexture(texture, nullptr, nullptr, &WINDOW_WIDTH, &WINDOW_HEIGHT);

			while (running) {
				HandleWindowEvent();
				Render_Another_Menu(texture);
			}
		}
				
		return;
	}

	void HandleWindowEvent() {
		if (SDL_PollEvent(&Framework::event)) {
			if (SDL_QUIT == Framework::event.type) {
				running = false;
				exit(0);
			}
		}
	}

	void Render_Player() {
		SDL_RenderClear(renderer);
		map->drawMap();
		manager.draw();
		for (auto &enemy : vector_enemies) {
			SDL_RenderCopyEx(renderer, enemy.getEnemyTexture(), &enemy.get_src_rec(), &enemy.get_dest_rec(), enemy.get_angle(), NULL, SDL_FLIP_NONE);
		}
		for (auto &bullet : *vector_bullets){
			SDL_RenderCopyEx(renderer, bullet.getTexture(), &bullet.get_src_rec(), &bullet.get_dest_rec(), bullet.get_angle(), NULL, SDL_FLIP_NONE);
		}

		SDL_RenderPresent(renderer);
	}

	void Render_Another_Menu(SDL_Texture *texture) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	void Update() {
		moveEnemies(element);
		moveBullets();
		manager.refresh();
		manager.update();
	}

	int Close() override {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_SUCCESS;
	}

	const char* GetTitle() override {
		return "Tanks";
	}

private:
	int WINDOW_WIDTH, WINDOW_HEIGHT, count;
	bool FullScreen = false;
	SDL_Window * window;
	SDL_Surface *screen;
};

std::vector<std::pair <int, int>> set_vector_free_position(const std::vector<std::vector<int>>& element) {
	std::vector<std::pair <int, int>> temp;
	for (size_t i = 0; i < element.size(); i++) {
		for (size_t j = 0; j < element[i].size(); j++) {
			if (element[i][j] == 0)
				temp.push_back(std::make_pair(i, j));
		}
	}
	return temp;
}

std::pair <int, int> take_free_spase(std::vector<std::pair <int, int>>& vector_space) {
	if (!vector_space.empty()) {
		int random = rand() % static_cast<int>(vector_space.size());
		std::pair <int, int> free = std::make_pair(vector_space[random].first, vector_space[random].second);
		vector_space.erase(vector_space.begin() + random);

		return free;
	}
	return {};
}


void show_help() {
	std::cerr << "Help Menu\n"
		<< "\t-h,--help\t\tShow this help message\n"
		<< "\t-window, \tSet Window Size\n"
		<< "\t\t without parametr, \tFull Screen = True\n"
		<< "\t\t with parametr \t\tlike 800x600"
		<< std::endl;
}

int run(Framework* Battle_Game) {
	Battle_Game->Init();
	Battle_Game->Close();
	return 0;
}

// Get the number of milliseconds since library initialization.
unsigned int getTickCount() {
	return SDL_GetTicks();
}

std::pair <int, int> parse_argv2(const std::string& str) {
	char separator = 'x';
	if (size_t pos = str.find(separator) == std::string::npos) {
		std::cout << "Error: Wrong separator" << std::endl;
		exit(0);
	}
	std::string width = str.substr(0, str.find(separator));
	std::string height = str.substr(width.size() + 1);

	return std::make_pair(stoi(width), stoi(height));
}

int return_game() {
	return run(new MyFramework());
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	for (size_t i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) {
			show_help();
			return 0;
		}
		else if (arg == "-window") {
			if (i + 1 < argc) {
				if (argc > 3)
					return_game();
				std::pair<int, int> p = parse_argv2(argv[++i]);
				MyFramework *Battle_Game = new MyFramework(p.first, p.second, false);
				return run(Battle_Game);
			}
			else {
				MyFramework *Battle_Game = new MyFramework(0, 0, SDL_WINDOW_FULLSCREEN);
				return run(Battle_Game);
			}
		}
	}
	return_game();
}