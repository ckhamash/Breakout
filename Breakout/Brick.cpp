#include "Brick.h"
#include "Game.h"

Brick::Brick() { }

Brick::Brick(sf::Vector2f position, sf::Vector2f dimensions, sf::Color color, int scoreValue) {
	rect.left = position.x;
	rect.top = position.y;

	rect.width = dimensions.x;
	rect.height = dimensions.y;

	verts = sf::VertexArray(sf::TrianglesFan, 4);
	verts[0].color = color;
	verts[1].color = color;
	verts[2].color = color;
	verts[3].color = color;

	isDying = false, isDead = false;
	deathTimer = sf::Clock();
	deathTime = Game::INIT_BRICK_DEATH_TIME;
	value = scoreValue;
}

Brick::~Brick() { }

sf::Rect<float> Brick::getRect() { return rect; }

void Brick::setRect(sf::Rect<float> rectangle) { rect = rectangle; }

int Brick::getValue() { return value; }

void Brick::hit() {
	isDying = true;
	deathTimer.restart();
}

void Brick::update(sf::RenderWindow &window) {
	if (isDying && deathTimer.getElapsedTime().asSeconds() < deathTime) {

	}
	else if (isDying)
		isDead = true;
}

void Brick::draw(sf::RenderWindow &window) {
	verts[0].position = sf::Vector2f(rect.left, rect.top);
	verts[1].position = sf::Vector2f(rect.left + rect.width, rect.top);
	verts[2].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	verts[3].position = sf::Vector2f(rect.left, rect.top + rect.height);

	window.draw(verts);
}