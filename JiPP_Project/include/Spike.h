#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <math.h>

class Spike
{
public:
	double area;
	std::array<sf::Vector2f, 3> vertices;
	sf::CircleShape shape;
	void calculateArea();
	double calculateArea(sf::Vector2f &a, sf::Vector2f &b, sf::Vector2f &c);
	Spike();
	~Spike();
};
