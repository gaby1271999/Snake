#include "Snake.h"

Snake::Snake(int x, int y, sf::Color c) {
	getLocations().push_back(Location(x, y));
	color = c;
}

Snake::~Snake() {
}

std::vector<Location> & Snake::getLocations() {
	return locations;
}

bool Snake::onSnake(int x, int y) {
	for (Location loc : getLocations()) {
		if (loc.getXPos() == x && loc.getYPos() == y) {
			return true;
		}
	}

	return false;
}
