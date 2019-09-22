#pragma once
#include <string>

class Location {

	public:
		Location(int x, int y);
		~Location();

		int getXPos();
		int getYPos();

		std::string toString() {
			return std::to_string(getXPos()) + " " + std::to_string(getYPos());
		}
	private:
		int xPos, yPos;
};

