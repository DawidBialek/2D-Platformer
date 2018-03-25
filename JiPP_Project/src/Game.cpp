#include "../include/stdafx.h"
#include "../include/Game.h"


Game::Game():window()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "2D Platformer");
	window->setVerticalSyncEnabled(1);
	window->setFramerateLimit(60);
	state = 0;
	screens.push_back(std::make_shared<MainMenuScreen>(window));
	screens.push_back(std::make_shared<GameScreen>(window));
	screens.push_back(std::make_shared<EditorScreen>(window));
}

Game::~Game()
{
}

void Game::run()
{
	//strange things happens here
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		this->update();
		window->clear();
		window->display();
	}
}

void Game::update()
{
	while (state >= 0)
	{
		std::cout << "In update " << std::endl;
		state = screens[state]->run();
	}
	window->close();
}
