#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
	static int maxTextWidth, widestTextPosition;
	sf::RectangleShape background;
	sf::Text text;
	Button();
	Button(std::string str);
	~Button();
};

