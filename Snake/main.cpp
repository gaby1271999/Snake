#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Snake.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int BOX_SIZE = 50;
int movementX = 1;
int movementY = 0;

void renderingThread(sf::RenderWindow* window) {
	window->setActive(true);

	sf::Clock clock;
	sf::Time t = sf::milliseconds(500);

	sf::RectangleShape rectangle(sf::Vector2f(50.0f, 50.0f));
	rectangle.setFillColor(sf::Color::Green);

	srand((int)time(0));
	int x = rand() % (WIDTH / BOX_SIZE), y = rand() % (HEIGHT / BOX_SIZE);
	Snake snake(x, y, sf::Color::Black);

	while (window->isOpen())
	{
		window->clear(sf::Color::Red);

		rectangle.setPosition(x*BOX_SIZE, y*BOX_SIZE);
		window->draw(rectangle);

		if (clock.getElapsedTime() >= t) {
			//x += 50.0f;
			clock.restart();
		}


		window->display();
	}
}


int main() {
	std::vector<Location> locs;
	locs.push_back(Location(5, 6));
	locs.push_back(Location(541, 54864));

	for (Location i : locs) {
		std::cout << i.toString() << std::endl;
	}

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake");

	window.setActive(false);

	sf::Thread thread(&renderingThread, &window);
	thread.launch();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				movementX = -1;
				movementY = 0;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				movementX = 1;
				movementY = 0;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				movementX = 0;
				movementY = -1;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				movementX = 0;
				movementY = 1;
			}
		}
	}

	return 0;
}