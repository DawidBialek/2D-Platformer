#pragma once
#include "AbstractScreen.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Spike.h"

class EditorScreen : public AbstractScreen
{
	std::string currentShapeType;
	sf::RectangleShape shape, levelStart, levelEnd;
	Spike spike;
	std::vector<Spike> spikeVec;
	std::vector<sf::RectangleShape> recVec;
	sf::Vector2i previousMousePosition, spikeSeriesStartPosition;
	sf::Clock startDelta;
	bool wasLeftMouseClicked, wasRightMouseClicked, wasDeleteClicked, isLevelStartPlaced, isLevelEndPlaced,
		wasUpPressed, wasDownPressed, spikeSeriesSet;

	bool isColliding();
	void checkCurrentState();
	void addRectangleShape();
	void addSpikeShape();
	void addStartShape();
	void addEndShape();
	void rotateSpike();
	void removeRectangleShape();
	void removeSpikeShape();
	void removeStartShape();
	void removeEndShape();
	void transformRectangleShape();
	void saveFile(std::string name);
public:
	EditorScreen(sf::RenderWindow *window);
	~EditorScreen();

	int run();
};

