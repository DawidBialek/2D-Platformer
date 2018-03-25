#include "../include/Spike.h"



void Spike::calculateArea()
{
	area = (vertices[0].x*(vertices[1].y - vertices[2].y) + vertices[1].x*(vertices[2].y - vertices[0].y) + vertices[2].x*(vertices[0].y - vertices[1].y)) / 2;
}

double Spike::calculateArea(sf::Vector2f &a, sf::Vector2f &b, sf::Vector2f &c)
{
	return std::abs((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2);
}

Spike::Spike()
{
}


Spike::~Spike()
{
}
