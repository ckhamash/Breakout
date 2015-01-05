#pragma once
#include "SFML\Graphics.hpp"
#include <math.h>

class Player {
private:
	sf::Rect<float> rect;
	sf::VertexArray verts;
	float moveSpeed;

	bool left, right;
public:
	Player();
	Player(sf::Vector2f position, sf::Vector2f dimensions, float speed);
	~Player();

	sf::Rect<float> getRect();

	void moveLeft();
	void moveRight();

	void checkBounds(float boundsWidth);

	void update(sf::RenderWindow &window, float secondsSinceLastFrame);
	void draw(sf::RenderWindow &window);
};
