#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <fstream>
#include <random>
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "TempTextManager.h"
#include "SoundManager.h"


class Game {
public:
	// Player values
	static const sf::Vector2f INIT_PLAYER_LOCATION;
	static const sf::Vector2f INIT_PLAYER_DIMENSION;
	static const sf::Vector2f INIT_ICON_DIMENSION;
	static const float INIT_PLAYER_SPEED;
	static const int MAX_PLAYER_LIVES;
	// Ball values
	static const sf::Vector2f INIT_BALL_DIMENSION;
	static const sf::Vector2f INIT_BALL_VELOCITY;
	static const float BALL_TURN_SPEED;
	// Brick values
	static const sf::Vector2f INIT_BRICK_DIMENSION;
	static const float INIT_BRICK_DEATH_TIME;
	static const float INIT_BRICK_WAVE_TIME;
	static const float INIT_BRICK_SPAWN_CHANCE;
	static const int MAX_BRICK_ROWS;
	// Laser values
	static const float LASER_SPEED;
	// UI values
	static const std::string UI_FONT_FILE;

private:
	int score, hiScore, lifeCount, comboMultiplier, brickColor, level, levelMultiplier;
	bool canLaunchBall;
	Player player;
	Ball ball;
	std::vector<Brick> bricks;
	std::vector<sf::Vector2f> lasers;
	sf::Clock frameTimer, spawnTimer;
	sf::Font font;
	sf::Text scoreText, lifeText, livesText, gameOverText, hiScoreText, levelMultiplierText;
	TempTextManager comboTexts, levelUpTexts;
	sf::Color colorWheel[6];
	
	std::random_device randomEngine;
	std::uniform_real_distribution<float> percentDistribution;

	SoundManager soundManager;
public:
	Game();
	Game(sf::RenderWindow &window);
	~Game();

	// logic for when the ball collides with another object
	void brickCollision(sf::Rect<float> intersection, sf::Rect<float> other);
	void playerCollision(sf::Rect<float> intersection, sf::Rect<float> other);
	void turnBall(float ballCenterX, float playerCenterX);

	void saveHiScore();
	void levelUp();
	void respawn();
	void restart(sf::RenderWindow &window);

	void spawnBricks(sf::RenderWindow &window);
	void pushBricksDown();
	void fireLasers(sf::RenderWindow &window);
	void drawLaser(sf::RenderWindow &window, sf::Vector2f laser);

	void start();
	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
};