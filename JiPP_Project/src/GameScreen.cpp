#include "../include/stdafx.h"
#include "../include/GameScreen.h"
#include <SFML\Graphics.hpp>


GameScreen::GameScreen(sf::RenderWindow *window)
{
	std::cout << "GameScreen ctor" << std::endl;
	this->window = window;
	levelNumber = 1;
	font.loadFromFile("fonts/homespun.ttf");
	playerTime.setFont(font);
	playerRecord.setFont(font);
	playerTime.setPosition(sf::Vector2f(10, 0));
	playerRecord.setPosition(sf::Vector2f(10, 40));
}


GameScreen::~GameScreen()
{
}

int GameScreen::run()
{
	level.loadFormFile(std::to_string(levelNumber));
	player.load(level);
	clock.restart();

	std::fstream fstr("levels/Records.txt");
	std::string record;
	if (fstr)
	{
		for (int i = 1; i <= levelNumber; i++)
		{
			std::getline(fstr, record);
		}
	}
	else
		std::cout << "Blad :C" << std::endl;
	playerRecord.setString(record);
	fstr.close();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					levelNumber = 1;
					return 0;
				}
				if (event.key.code == sf::Keyboard::R)
				{
					player.resetPlayer();
				}
			}
		}
		time = clock.getElapsedTime();
		clock.restart();
		
		player.control(time);
		player.checkCollisions(level.rectangleVector, level.spikeVector, level.lowestRecPos);

		//will have to place it some better place later
		if (player.shape.getGlobalBounds().intersects(level.levelEnd.getGlobalBounds()))
		{
			std::cout << levelNumber << ": " << player.playerTimer.getElapsedTime().asMilliseconds() << std::endl;
			levelNumber++;
			level.loadFormFile(std::to_string(levelNumber));
			player.load(level);
			clock.restart();
			/*if (playerTime.getString() < playerRecord.getString())
			{
				for (int i = 1; i <= levelNumber; i++) {}
				std::fstream fstr2("levels/Records.txt",std::ios::out || std::ios::app)
			}*/
		}
		playerTime.setString(std::to_string(player.playerTimer.getElapsedTime().asMilliseconds()));
		//std::cout << player.playerTimer.getElapsedTime().asMilliseconds() << std::endl;
		
		if (levelNumber > 8)
		{
			levelNumber = 1;
			return 0;
		}
		
		window->clear();
		for (auto &e : level.rectangleVector)
			window->draw(e);
		for (auto &e : level.spikeVector)
			window->draw(e.shape);
		window->draw(level.levelStart);
		window->draw(level.levelEnd);
		window->draw(player.shape);
		window->draw(playerTime);
		//window->draw(playerRecord);
		window->display();
	}
	return 0;
}