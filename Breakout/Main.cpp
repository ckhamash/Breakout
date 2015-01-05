#include "SFML\Graphics.hpp"
#include <iostream>
#include <list>
#include "Game.h"

// Player values
const sf::Vector2f Game::INIT_PLAYER_LOCATION = sf::Vector2f(500, 500);
const sf::Vector2f Game::INIT_PLAYER_DIMENSION = sf::Vector2f(100, 20);
const sf::Vector2f Game::INIT_ICON_DIMENSION = sf::Vector2f(60, 15);
const float Game::INIT_PLAYER_SPEED = 500; // pixels per second
const int Game::MAX_PLAYER_LIVES = 3;
// Ball values
const sf::Vector2f Game::INIT_BALL_DIMENSION = sf::Vector2f(4, 4);
const sf::Vector2f Game::INIT_BALL_VELOCITY = sf::Vector2f(100, -300); // pixels per second
const float Game::BALL_TURN_SPEED = 3; // pixels per second per pixel from center of player
// Brick values
const sf::Vector2f Game::INIT_BRICK_DIMENSION = sf::Vector2f(40, 20);
const float Game::INIT_BRICK_DEATH_TIME = 0; // time in seconds for bricks to die
const float Game::INIT_BRICK_WAVE_TIME = 15; // initial time in seconds until the next wave of bricks
const float Game::INIT_BRICK_SPAWN_CHANCE = 0.6f; // chance brick will spawn
const int Game::MAX_BRICK_ROWS = 16;
// Laser values
const float Game::LASER_SPEED = 500;
// UI values
const std::string Game::UI_FONT_FILE = "game_over.ttf";

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Breakout", sf::Style::Close);
	Game game = Game(window);
	game.restart(window);
	while (window.isOpen()) {
		game.update(window);
	}
}