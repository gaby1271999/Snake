#include "Snake.h"

Snake::Snake(int x, int y, sf::Color c) {
	Location location(x, y);
	getLocations().push_back(location);
	color = c;
	std::cout << "created" << getLocations().front().getXPos() << getLocations().front().getYPos() << std::endl;
}

Snake::~Snake() {
}

std::vector<Location> & Snake::getLocations() {
	return locations;
}
