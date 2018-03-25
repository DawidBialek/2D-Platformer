#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
class Menu
{
	//sf::RenderWindow window;
	sf::Font font;
	sf::Text title, start, options, exit, back;
public:
	Menu();
	~Menu();
	void loadFont(std::string name);
	void setFont(sf::Font &font);
	void setTextPosition();

	void showMainMenu(sf::RenderWindow &window);
};

