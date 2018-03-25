#pragma once
#include <SFML/Graphics.hpp>
class App
{
	sf::RenderWindow* window;
public:
	App();
	virtual ~App() = 0;
};

