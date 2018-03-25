#include "../include/stdafx.h"
#include "../include/Menu.h"


Menu::Menu()
{
	loadFont("fonts/homespun.ttf");
	setFont(font);
	setTextPosition();
}


Menu::~Menu()
{
}

void Menu::loadFont(std::string name)
{
	try
	{
		if (!font.loadFromFile(name))
			throw 001;
	}
	catch (int errorCode)
	{
		//std::cout << "Error! Code: " << errorCode << " Could not open font file!" << std::endl
		std::cout << "Terminating program..." << std::endl;
		std::terminate();
	}
}
void Menu::setFont(sf::Font &font)
{
	title.setFont(font);
	start.setFont(font);
	options.setFont(font);
	exit.setFont(font);
	back.setFont(font);
}

void Menu::setTextPosition()
{
	title.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width/2-title.getGlobalBounds().width/2, sf::VideoMode::getDesktopMode().height/20));
}

void Menu::showMainMenu(sf::RenderWindow &window)
{

	/*sf::Event event;
	sf::CircleShape cir(10);
	cir.setFillColor(sf::Color::Blue);

	title.setCharacterSize(20);
	title.setString("Imba gra");
	title.setColor(sf::Color::Green);
	while (currentState == MAIN_MENU)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		std::cout << "test" << std::endl;
		window.clear();
		window.draw(title);
		window.draw(cir);
		window.display();
	}*/
}
