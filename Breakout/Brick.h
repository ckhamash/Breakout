#pragma once
#include "SFML\Graphics.hpp"

class Brick {
private:
	sf::Rect<float> rect;
	sf::VertexArray verts;
	int value;
	sf::Clock deathTimer;
	float deathTime;
public:
	bool isDying, isDead;

	Brick();
	Brick(sf::Vector2f position, sf::Vector2f dimensions, sf::Color color = sf::Color::Red, int scoreValue = 10);
	~Brick();

	sf::Rect<float> getRect();
	void setRect(sf::Rect<float> rectangle);
	int getValue();

	void hit();

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
};

