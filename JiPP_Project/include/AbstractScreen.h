#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class AbstractScreen
{
public:
	sf::RenderWindow *window;
	sf::Clock clock;
	sf::Time time;
	virtual int run() = 0;
};

