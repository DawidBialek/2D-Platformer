#include "../include/stdafx.h"
#include "../include/MainMenuScreen.h"


MainMenuScreen::MainMenuScreen(sf::RenderWindow *window)
{
	this->window = window;
	loadFont("fonts/homespun.ttf");

	title.setString("2D Platformer");
	title.setFont(font);
	title.setColor(sf::Color::Green);
	title.setCharacterSize(window->getSize().x/13);
	title.setPosition(sf::Vector2f(window->getSize().x / 2 - title.getGlobalBounds().width / 2, window->getSize().y / 15));
	setButtonArray();
}


MainMenuScreen::~MainMenuScreen()
{
}

void MainMenuScreen::loadFont(std::string name)
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
void MainMenuScreen::setButtonArray()
{
	int textSize = window->getSize().x / 21;

	buttonArray[0].text.setString("Start");
	buttonArray[1].text.setString("Level editor");
	buttonArray[2].text.setString("Options");
	buttonArray[3].text.setString("Exit");

	for (int i=0; i<buttonArray.size();i++)
	{
		buttonArray[i].text.setFont(font);
		buttonArray[i].text.setColor(sf::Color::White);
		buttonArray[i].text.setCharacterSize(textSize);
		buttonArray[i].text.setPosition(sf::Vector2f(window->getSize().x / 2 - buttonArray[i].text.getGlobalBounds().width / 2, ((window->getSize().y / 15) + (i + 1) * window->getSize().y / 7) + title.getGlobalBounds().height));
		if (Button::maxTextWidth < buttonArray[i].text.getGlobalBounds().width)
		{
			Button::maxTextWidth = buttonArray[i].text.getGlobalBounds().width;
		}
		if (Button::widestTextPosition > buttonArray[i].text.getPosition().x)
		{
			Button::widestTextPosition = buttonArray[i].text.getPosition().x;
		}
	}
	for (auto &e : buttonArray)
	{
		e.background.setSize(sf::Vector2f(Button::maxTextWidth, buttonArray[1].text.getPosition().y - buttonArray[0].text.getPosition().y));
		//std::cout << e.text.getPosition().y << std::endl;
		e.background.setPosition(Button::widestTextPosition, e.text.getPosition().y - (0.11*e.background.getGlobalBounds().height));
		e.background.setFillColor(sf::Color(0,255,0,sf::Uint32(0)));
		//e.background.setOutlineColor(sf::Color::Red);
		//e.background.setOutlineThickness(1);
	}
}
int MainMenuScreen::checkButtons()
{
	for (int i = 0; i < buttonArray.size(); i++)
	{
		if (buttonArray[i].background.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			buttonArray[i].text.setColor(sf::Color(0, 128, 0));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				//some problems with vector after clicking exit!
				if (i != buttonArray.size() - 1)
					return i + 1;
				else
					return -1;
		}
		else if (buttonArray[i].text.getColor() != sf::Color::White)
			buttonArray[i].text.setColor(sf::Color::White);
	}
	return -2;
}

int MainMenuScreen::run()
{
	int temp;
	while (window->isOpen())
	{
		//std::cout << "In run";
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					return -1;
			}
		}

		//checking if checkButtons() returned change of state, if not it will returne -2
		temp = checkButtons();
		//std::cout << temp << std::endl;
		if (temp != -2)
			return temp;

		window->clear();
		window->draw(title);
		for (auto &e : buttonArray)
		{
			window->draw(e.text);
			window->draw(e.background);
		}
		window->display();
	}
	return 0;
}
