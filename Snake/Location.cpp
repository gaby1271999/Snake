#include "Location.h"



Location::Location(int x, int y) {
	xPos = x;
	yPos = y;
}


Location::~Location() {
}

int & Location::getXPos() {
	return xPos;
}

int & Location::getYPos() {
	return yPos;
}

void Location::setXPos(int x) {
	xPos = x;
}

void Location::setYPos(int y) {
	yPos = y;
}