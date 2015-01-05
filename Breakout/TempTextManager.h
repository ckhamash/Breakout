#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class TempTextManager {
private:
	sf::Font defaultFont;
	float lifeTime;
	int defaultCharSize;
	sf::Color defaultColor;
	sf::Vector2f moveVelocity;

	std::vector<sf::Text> texts;
	std::vector<sf::Clock> timers;

public:
	TempTextManager();
	TempTextManager(sf::Font font, float time, int size, sf::Color color, sf::Vector2f velocity = sf::Vector2f(0, 0));
	~TempTextManager();
	
	sf::Text sampleText(std::string string);

	void addText(std::string string, sf::Vector2f position);

	void update(sf::RenderWindow &window, float secondsSinceLastFrame);
	void draw(sf::RenderWindow &window);
};

