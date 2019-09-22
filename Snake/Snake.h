#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Location.h"

class Snake {

	public:
		Snake(int x, int y, sf::Color c);
		~Snake();

		std::vector<Location> & getLocations();

	private:
		std::vector<Location> locations;
		sf::Color color;

};

