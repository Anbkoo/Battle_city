#include "SDL.h"
#include "SDL_image.h"
#include "Framework.h"
#include "Map.h"
#include "Component.h"
#include <math.h>

bool check(const std::vector<std::vector<int>>& element_map, int i, int j) {
	if (element_map[j][i] == 2 || element_map[j][i] == 3 || element_map[j][i] == 0)
		return true;
	return false;
}

bool Collision::check_coll(std::pair <int, int> size_el, int pos_x, int pos_y, const std::vector<std::vector<int>>& element_map, char sight, int _WINDOW_WIDTH, int _WINDOW_HEIGHT) {
	double i = pos_x / static_cast<double>(_WINDOW_WIDTH / 16);
	double j = pos_y / static_cast<double>(_WINDOW_HEIGHT / 16);

	if (sight == 'U') {
		if (check(element_map, static_cast<int>(i), static_cast<int>(j)) && check(element_map, ceil(i), static_cast<int>(j)))
			return true;
	} else if (sight == 'D') {
		if (check(element_map, static_cast<int>(i), ceil(j)) && check(element_map, ceil(i), ceil(j)))
			return true;
	} else if (sight == 'L') {
		if (check(element_map, static_cast<int>(i), static_cast<int>(j)) && check(element_map, static_cast<int>(i), ceil(j)))
			return true;
	} else if (sight == 'R') {
		if (check(element_map, ceil(i), static_cast<int>(j)) && check(element_map, ceil(i), ceil(j)))
			return true;
	}
	return false;
}