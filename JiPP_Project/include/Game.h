#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Menu.h"
#include "MainMenuScreen.h"
#include "AbstractScreen.h"
#include "GameScreen.h"
#include "EditorScreen.h"

class Game
{
	int state;
	sf::RenderWindow win;
public:
	sf::RenderWindow *window;
	std::vector<std::shared_ptr<AbstractScreen>> screens;
	Game();
	~Game();
	void run();
	void update();
};

