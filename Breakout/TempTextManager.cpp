#include "TempTextManager.h"


TempTextManager::TempTextManager() {}

TempTextManager::TempTextManager(sf::Font font, float time, int size, sf::Color color, sf::Vector2f velocity) {
	defaultFont = font;
	lifeTime = time;
	defaultCharSize = size;
	defaultColor = color;
	moveVelocity = velocity;
}

TempTextManager::~TempTextManager() { }

sf::Text TempTextManager::sampleText(std::string string) {
	sf::Text newText = sf::Text(string, defaultFont, defaultCharSize);
	newText.setColor(defaultColor);
	return newText;
}

void TempTextManager::addText(std::string string, sf::Vector2f position) {
	sf::Text newText = sf::Text(string, defaultFont, defaultCharSize);
	newText.setColor(defaultColor);
	newText.setPosition(position);
	texts.push_back(newText);
	timers.push_back(sf::Clock());
}

void TempTextManager::update(sf::RenderWindow &window, float secondsSinceLastFrame) {
	// remove old texts
	std::vector<int> toBeRemoved;
	for (int i = 0; i < texts.size(); i++) {
		if (timers[i].getElapsedTime().asSeconds() > lifeTime)
			toBeRemoved.push_back(i);
	}
	if (!toBeRemoved.empty()) {
		for (int i = toBeRemoved.size() - 1; i > -1; i--) {
			texts.erase(texts.begin() + toBeRemoved[i]);
			timers.erase(timers.begin() + toBeRemoved[i]);
		}
	}

	// update texts
	for (int i = 0; i < texts.size(); i++) {
		texts[i].setPosition(texts[i].getPosition() + moveVelocity * secondsSinceLastFrame);
	}
}

void TempTextManager::draw(sf::RenderWindow &window) {
	for each (sf::Text text in texts) {
		window.draw(text);
	}
}