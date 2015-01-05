#pragma once
#include "SFML\Graphics.hpp"

class Ball {
private:
	sf::Rect<float> rect;
	sf::VertexArray verts;
	sf::Vector2f velocity;
public:
	bool isDead;
	bool hitTop;

	Ball();
	explicit Ball(sf::Vector2f position, sf::Vector2f dimensions, sf::Vector2f initVelocity);
	~Ball();

	sf::Rect<float> getRect();
	void setRect(sf::Rect<float> rectangle);
	sf::Vector2f getVelocity();

	void bounceY();
	void bounceX();
	void changeVelocity(sf::Vector2f vector);

	void checkBounds(sf::Vector2f bounds);

	void update(sf::RenderWindow &window, float secondsSinceLastFrame);
	void draw(sf::RenderWindow &window);
};
