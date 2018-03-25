#pragma once
#include <iostream>
#include <fstream>
#include "AbstractScreen.h"
#include "Button.h"
#include "Level.h"
#include "Player.h"

class GameScreen : public AbstractScreen
{
	Level level;
	Player player;
	int levelNumber;
	sf::Text playerTime, playerRecord;
	sf::Font font;
public:
	GameScreen(sf::RenderWindow *window);
	~GameScreen();
	int run();
};

