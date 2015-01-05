#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class TextManager {
private:
	std::vector<sf::Text> texts;
	sf::Font defaultFont;
public:
	TextManager();
	~TextManager();
};

