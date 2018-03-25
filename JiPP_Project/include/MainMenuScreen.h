#pragma once
#include "AbstractScreen.h"
#include "Button.h"
#include <memory>
#include <iostream>
#include <array>

class MainMenuScreen : public AbstractScreen
{
	sf::Font font;
	sf::Text title;
	std::array<Button,4> buttonArray;
	void loadFont(std::string name);
	void setButtonArray();
	int checkButtons();
public:
	MainMenuScreen(sf::RenderWindow *window);
	~MainMenuScreen();

	int run();
};

