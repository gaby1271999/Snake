#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Snake.h"
#include "Location.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int BOX_SIZE = 50;
int movementX = 1;
int movementY = 0;

std::vector<Location> world;

Location findFoodLocation(Snake& snake) {
	std::vector<Location> world;

	for (int x = 0; x < (WIDTH / BOX_SIZE); x++) {
		for (int y = 0; y < (HEIGHT / BOX_SIZE); y++) {
			if (!snake.onSnake(x, y)) {
				world.push_back(Location(x, y));
			}
		}
	}

	return world[rand() % world.size()];
}

void renderingThread(sf::RenderWindow* window) {
	window->setActive(true);

	sf::Clock clock;
	sf::Time t = sf::milliseconds(500);

	sf::RectangleShape snakeHead(sf::Vector2f(50.0f, 50.0f));
	snakeHead.setFillColor(sf::Color::Blue);
	sf::RectangleShape foodRect(sf::Vector2f(50.0f, 50.0f));
	foodRect.setFillColor(sf::Color::Green);

	srand((int)time(0));
	int x = rand() % (WIDTH / BOX_SIZE), y = rand() % (HEIGHT / BOX_SIZE);
	Snake snake(x, y, sf::Color::Black);

	Location food = findFoodLocation(snake);

	while (window->isOpen())
	{
		window->clear(sf::Color::Red);

		snakeHead.setPosition(snake.getLocations().front().getXPos()*BOX_SIZE, snake.getLocations().front().getYPos()*BOX_SIZE);
		foodRect.setPosition(food.getXPos()*BOX_SIZE, food.getYPos()*BOX_SIZE);

		window->draw(foodRect);
		window->draw(snakeHead);
		if (snake.getLocations().size() > 1) {
			for (int i = 1; i < snake.getLocations().size(); i++) {
				sf::RectangleShape bodypart(sf::Vector2f(50.0f, 50.0f));
				bodypart.setFillColor(sf::Color::Cyan);
				bodypart.setPosition(snake.getLocations()[i].getXPos()*BOX_SIZE, snake.getLocations()[i].getYPos()*BOX_SIZE);
				window->draw(bodypart);
			}
		}

		if (clock.getElapsedTime() >= t) {
			int x = snake.getLocations().front().getXPos();
			int y = snake.getLocations().front().getYPos();

			if (x == food.getXPos() && y == food.getYPos()) {
				snake.getLocations().push_back(food);
				food = findFoodLocation(snake);
			}

			int newX = x + movementX;
			int newY = y + movementY;
			
			if (newX < 0) {
				snake.getLocations().front().setXPos((WIDTH / BOX_SIZE) - 1);
			} else if (newX > (WIDTH / BOX_SIZE) - 1) {
				snake.getLocations().front().setXPos(0);
			} else if (newY < 0) {
				snake.getLocations().front().setYPos((HEIGHT / BOX_SIZE) - 1);
			} else if (newY > (HEIGHT / BOX_SIZE) - 1) {
				snake.getLocations().front().setYPos(0);
			} else {
				snake.getLocations().front().setXPos(newX);
				snake.getLocations().front().setYPos(newY);
			}

			if (snake.getLocations().size() > 1) {
				for (int i = (snake.getLocations().size()-1); i >= 1; i--) {
					if (i == 1) {
						snake.getLocations()[i].setXPos(x);
						snake.getLocations()[i].setYPos(y);
					} else {
						snake.getLocations()[i].setXPos(snake.getLocations()[i-1].getXPos());
						snake.getLocations()[i].setYPos(snake.getLocations()[i-1].getYPos());
					}
				}
			}

			clock.restart();
		}


		window->display();
	}
}


int main() {
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
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				movementX = 0;
				movementY = 1;
			}
		}
	}

	return 0;
}