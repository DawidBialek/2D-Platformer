#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <array>
#include<SFML/Graphics.hpp>
#include "Spike.h"

class Level
{
	std::string name;
	std::vector<sf::RectangleShape> rectangleVector;
	std::vector<Spike> spikeVector;
	sf::Vector2f lowestRecPos;
	friend class GameScreen;
public:
	sf::RectangleShape levelStart, levelEnd;

	Level();
	Level(std::string name);
	~Level();
	void loadFormFile(std::string name);
};

