#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "Level.h"
class Player
{
	sf::RectangleShape shape;
	friend class GameScreen;
	sf::Vector2f previousPosition, startingPosition, velocity;
	int acceleration;
	bool collisionLeft, collisionRight, jumpPressed, isJumping;
	sf::Clock playerTimer;
	void resetPlayer();
	//friend class Level;
public:
	Player();
	~Player();
	void load(Level level);
	void checkCollisions(std::vector<sf::RectangleShape> rectangleVector, std::vector<Spike> spikeVector, sf::Vector2f lowestRecPos);
	void control(sf::Time time);

};

