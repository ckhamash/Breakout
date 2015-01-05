#include "Ball.h"
#include "Game.h"

Ball::Ball() {
	isDead = hitTop = false;
	rect.left = 0;
	rect.top = 0;

	rect.width = Game::INIT_BALL_DIMENSION.x;
	rect.height = Game::INIT_BALL_DIMENSION.y;

	verts = sf::VertexArray(sf::TrianglesFan, 4);
	verts[0].color = sf::Color::White;
	verts[1].color = sf::Color::White;
	verts[2].color = sf::Color::White;
	verts[3].color = sf::Color::White;

	velocity = Game::INIT_BALL_VELOCITY;
}

Ball::Ball(sf::Vector2f position, sf::Vector2f dimensions, sf::Vector2f initVelocity) {
	isDead = hitTop = false;
	rect.left = position.x;
	rect.top = position.y;

	rect.width = dimensions.x;
	rect.height = dimensions.y;

	verts = sf::VertexArray(sf::TrianglesFan, 4);
	verts[0].color = sf::Color::White;
	verts[1].color = sf::Color::White;
	verts[2].color = sf::Color::White;
	verts[3].color = sf::Color::White;

	velocity = initVelocity;
}

Ball::~Ball() { }

sf::Rect<float> Ball::getRect() { return rect; }

void Ball::setRect(sf::Rect<float> rectangle) { rect = rectangle; }

sf::Vector2f Ball::getVelocity() { return velocity; }

void Ball::bounceY() { velocity.y *= -1; }

void Ball::bounceX() { velocity.x *= -1; }

void Ball::changeVelocity(sf::Vector2f vector) { velocity += vector; }

void Ball::checkBounds(sf::Vector2f bounds) {
	if (rect.left < 0) {
		rect.left = 0;
		bounceX();
	}
	if (rect.top < 0) {
		rect.top = 0;
		bounceY();
		hitTop = true;
	}
	if (rect.left + rect.width > bounds.x) {
		rect.left = bounds.x - rect.width;
		bounceX();
	}
	if (rect.top + rect.height > bounds.y) {
		rect.top = bounds.y - rect.height;
		bounceY();
		isDead = true;
	}
}

void Ball::update(sf::RenderWindow &window, float secondsSinceLastFrame) {
	rect.left += velocity.x * secondsSinceLastFrame;
	rect.top += velocity.y * secondsSinceLastFrame;
	checkBounds(sf::Vector2f(window.getSize()));
}

void Ball::draw(sf::RenderWindow &window) {
	verts[0].position = sf::Vector2f(rect.left, rect.top);
	verts[1].position = sf::Vector2f(rect.left + rect.width, rect.top);
	verts[2].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	verts[3].position = sf::Vector2f(rect.left, rect.top + rect.height);

	window.draw(verts);
}