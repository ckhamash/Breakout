#include "Player.h"
#include "Game.h"

Player::Player() {
	rect.left = Game::INIT_PLAYER_LOCATION.x;
	rect.top = Game::INIT_PLAYER_LOCATION.y;

	rect.width = Game::INIT_PLAYER_DIMENSION.x;
	rect.height = Game::INIT_PLAYER_DIMENSION.y;

	verts = sf::VertexArray(sf::Quads, 8);
	verts[0].color = sf::Color::White;
	verts[1].color = sf::Color::Blue;
	verts[2].color = sf::Color::Blue;
	verts[3].color = sf::Color::White;
	verts[4].color = sf::Color::Blue;
	verts[5].color = sf::Color::White;
	verts[6].color = sf::Color::White;
	verts[7].color = sf::Color::Blue;

	moveSpeed = Game::INIT_PLAYER_SPEED;

	left = false;
	right = false;
}

Player::Player(sf::Vector2f position, sf::Vector2f dimensions, float speed) {
	rect.left = position.x;
	rect.top = position.y;

	rect.width = dimensions.x;
	rect.height = dimensions.y;
	
	verts = sf::VertexArray(sf::Quads, 8);
	verts[0].color = sf::Color::White;
	verts[1].color = sf::Color::Blue;
	verts[2].color = sf::Color::Blue;
	verts[3].color = sf::Color::White;
	verts[4].color = sf::Color::Blue;
	verts[5].color = sf::Color::White;
	verts[6].color = sf::Color::White;
	verts[7].color = sf::Color::Blue;

	moveSpeed = speed;

	left = false;
	right = false;
}


Player::~Player() { }

sf::Rect<float> Player::getRect() { return rect; }

void Player::moveLeft() {
	left = true;
}

void Player::moveRight() {
	right = true;
}

void Player::checkBounds(float boundsWidth) {
	if (rect.left < 0)
		rect.left = 0;
	if (rect.left + rect.width > boundsWidth)
		rect.left = boundsWidth - rect.width;
}

void Player::update(sf::RenderWindow &window, float secondsSinceLastFrame) {
	checkBounds((float)window.getSize().x);
	if (left) {
		rect.left -= moveSpeed * secondsSinceLastFrame;
		left = false;
	}
	if (right) {
		rect.left += moveSpeed * secondsSinceLastFrame;
		right = false;
	}
}

void Player::draw(sf::RenderWindow &window) {
	verts[0].position = sf::Vector2f(rect.left, rect.top);
	verts[1].position = sf::Vector2f(rect.left + rect.width / 2, rect.top);
	verts[2].position = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height);
	verts[3].position = sf::Vector2f(rect.left, rect.top + rect.height);
	verts[4].position = verts[1].position;
	verts[5].position = sf::Vector2f(rect.left + rect.width, rect.top);
	verts[6].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	verts[7].position = verts[2].position;

	window.draw(verts);
}