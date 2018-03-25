#include "../include/stdafx.h"
#include "..\include\Level.h"


Level::Level()
{
	levelStart.setSize(sf::Vector2f(30, 30));
	levelEnd.setSize(sf::Vector2f(15, 60));
	levelStart.setFillColor(sf::Color(0, 255, 0, sf::Uint32(128)));
	levelEnd.setFillColor(sf::Color(0, 0, 255, sf::Uint32(128)));
}

Level::Level(std::string name):name(name)
{

}


Level::~Level()
{
}

void Level::loadFormFile(std::string name)
{
	rectangleVector.clear();
	spikeVector.clear();
	name = "levels/" + name + ".txt";
	//std::cout << name << std::endl;
	//"levels/test.txt"
	std::fstream fin(name, std::ios::in);
	if (fin)
	{
		std::string row;
		std::regex pattern1("(\\d*)x(\\d*) (\\d*)x(\\d*)");
		std::regex pattern2("(\\w*) (\\d*)x(\\d*) (\\d*)x(\\d*) (\\d*),(\\d*),(\\d*)");
		std::regex pattern3("(\\w*) (\\d*)x(\\d*) (\\d*),(\\d*)");
		std::smatch sm, sm2;

		//loading position of start and end of the level
		std::getline(fin, row);
		std::regex_search(row, sm, pattern1);
		levelStart.setPosition(sf::Vector2f(std::stoi(sm.str(1)), std::stoi(sm.str(2))));
		levelEnd.setPosition(sf::Vector2f(std::stoi(sm.str(3)), std::stoi(sm.str(4))));

		//returning to the beggining of the file
		fin.clear();
		fin.seekg(0, std::ios::beg);
		
		//loading rectangle, traingle and circle elements
		while (!fin.eof())
		{
			std::getline(fin, row);
			std::regex_search(row, sm, pattern2);
			std::regex_search(row, sm2, pattern3);

			if (sm.str(1) == "RectangleShape")
			{
				sf::RectangleShape rectangle;
				rectangle.setPosition(sf::Vector2f(std::stoi(sm.str(2)), std::stoi(sm.str(3))));
				rectangle.setSize(sf::Vector2f(std::stoi(sm.str(4)), std::stoi(sm.str(5))));
				rectangle.setFillColor(sf::Color(std::stoi(sm.str(6)),std::stoi(sm.str(7)),std::stoi(sm.str(8))));
				rectangleVector.push_back(rectangle);

			}
			else if (sm2.str(1) == "CircleShape")
			{
				Spike spike;
				spike.shape.setRadius(std::stoi(sm2.str(4)));
				spike.shape.setPointCount(std::stoi(sm2.str(5)));
				spike.shape.setPosition(sf::Vector2f(std::stoi(sm2.str(2)), std::stoi(sm2.str(3))));
				/*for (auto &e : sm2)
				{
					std::cout << e << std::endl;
				}*/
				spike.vertices[0].x = spike.shape.getPosition().x;
				spike.vertices[0].y = spike.shape.getPosition().y + spike.shape.getGlobalBounds().height;
				spike.vertices[1].x = spike.shape.getPosition().x + spike.shape.getGlobalBounds().width / 2;
				spike.vertices[1].y = spike.shape.getPosition().y;
				spike.vertices[2].x = spike.shape.getPosition().x + spike.shape.getGlobalBounds().width;
				spike.vertices[2].y = spike.vertices[0].y;

				//std::cout << spike.vertices[0].x << " " << spike.vertices[0].y << " " << spike.vertices[1].x  << " " << spike.vertices[1].y << " " << spike.vertices[2].x << " " << spike.vertices[2].y << std::endl;

				spike.calculateArea();
				//std::cout << spike.area << std::endl;

				spikeVector.push_back(spike);
			}
		}

		//will change this later
		for (auto &e : spikeVector)
		{
			e.shape.setFillColor(sf::Color(200, 200, 200));
		}

		fin.clear();
		fin.seekg(0, std::ios::beg);

		lowestRecPos = rectangleVector[0].getPosition();
		for (auto &e : rectangleVector)
		{
			if (e.getPosition().y > lowestRecPos.y)
				lowestRecPos = e.getPosition();
		}
	}
	else
		std::cout << "Blad! Zla nazwa poziomu!" << std::endl;
}
