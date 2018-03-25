#include "../include/stdafx.h"
#include "../include/EditorScreen.h"


bool EditorScreen::isColliding()
{
	for (auto &e : recVec)
	{
		if (shape.getGlobalBounds().intersects(e.getGlobalBounds()))
			return true;
	}
	return false;
}

void EditorScreen::checkCurrentState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		currentShapeType = "rectangle";
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		currentShapeType = "spike";
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		currentShapeType = "levelStart";
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		currentShapeType = "levelEnd";
}

void EditorScreen::addRectangleShape()
{
	//adds new shape to vector if left mouse if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasLeftMouseClicked && startDelta.getElapsedTime().asSeconds() > 0.5f)
	{
		recVec.push_back(shape);
		wasLeftMouseClicked = 1;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && wasLeftMouseClicked)
		wasLeftMouseClicked = 0;
}
void EditorScreen::addSpikeShape()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !wasLeftMouseClicked && startDelta.getElapsedTime().asSeconds() > 0.5f)
	{
		spikeVec.push_back(spike);
		wasLeftMouseClicked = 1;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && wasLeftMouseClicked)
		wasLeftMouseClicked = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		sf::Clock tempClock;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !spikeSeriesSet)
		{
			//tempClock.restart();
			spikeSeriesStartPosition = sf::Mouse::getPosition(*window);
			spikeSeriesSet = 1;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && spikeSeriesSet)
		{
			for (double i = spikeSeriesStartPosition.x; i < sf::Mouse::getPosition(*window).x; i += spike.shape.getGlobalBounds().width)
			{
				spike.shape.setPosition(sf::Vector2f(i, spikeSeriesStartPosition.y));
				spikeVec.push_back(spike);
			}
			spikeSeriesSet = 0;
		}

	}
}
void EditorScreen::addStartShape()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasLeftMouseClicked && startDelta.getElapsedTime().asSeconds() > 0.5f && !isLevelStartPlaced)
		isLevelStartPlaced = 1;
}
void EditorScreen::addEndShape()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasLeftMouseClicked && startDelta.getElapsedTime().asSeconds() > 0.5f && !isLevelEndPlaced)
		isLevelEndPlaced = 1;
}
void EditorScreen::rotateSpike()
{
	//spike rotating
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !wasUpPressed)
	{
		spike.shape.rotate(90);
		wasUpPressed = 1;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && wasUpPressed)
	{
		wasUpPressed = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !wasDownPressed)
	{
		spike.shape.rotate(-90);
		wasDownPressed = 1;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && wasDownPressed)
	{
		wasDownPressed = 0;
	}
}
void EditorScreen::removeRectangleShape()
{
	//removes object if right mouse is clicked
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && !wasDeleteClicked)
	{
		wasDeleteClicked = 1;
		for (auto &it = recVec.begin(); it != recVec.end();)
		{
			if (it->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))))
			{
				it = recVec.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && wasDeleteClicked)
		wasDeleteClicked = 0;
}
void EditorScreen::removeSpikeShape()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && !wasDeleteClicked)
	{
		wasDeleteClicked = 1;
		for (auto &it = spikeVec.begin(); it != spikeVec.end();)
		{
			if (it->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))))
			{
				it = spikeVec.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && wasDeleteClicked)
		wasDeleteClicked = 0;
}
void EditorScreen::removeStartShape()
{
	if (isLevelStartPlaced && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && levelStart.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))))
		isLevelStartPlaced = 0;
}
void EditorScreen::removeEndShape()
{
	if (isLevelEndPlaced && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && levelEnd.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))))
		isLevelEndPlaced = 0;
}
void EditorScreen::transformRectangleShape()
{
	//changing size of shape
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			shape.setSize(sf::Vector2f(shape.getSize().x - 15, shape.getSize().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			shape.setSize(sf::Vector2f(shape.getSize().x + 15, shape.getSize().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			shape.setSize(sf::Vector2f(shape.getSize().x, shape.getSize().y + 15));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			shape.setSize(sf::Vector2f(shape.getSize().x, shape.getSize().y - 15));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			shape.setSize(sf::Vector2f(shape.getSize().x - 1, shape.getSize().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			shape.setSize(sf::Vector2f(shape.getSize().x + 1, shape.getSize().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			shape.setSize(sf::Vector2f(shape.getSize().x, shape.getSize().y + 1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			shape.setSize(sf::Vector2f(shape.getSize().x, shape.getSize().y - 1));
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			shape.setSize(sf::Vector2f(shape.getSize().x - 5, shape.getSize().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			shape.setSize(sf::Vector2f(shape.getSize().x + 5, shape.getSize().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			shape.setSize(sf::Vector2f(shape.getSize().x, shape.getSize().y + 5));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			shape.setSize(sf::Vector2f(shape.getSize().x, shape.getSize().y - 5));
	}
}

void EditorScreen::saveFile(std::string name)
{
	name = "levels/" + name;
	//std::cout << name << std::endl;
	std::fstream fout(name, std::ios::out);
	if (fout)
	{
		fout << (int)levelStart.getPosition().x << "x" << (int)levelStart.getPosition().y << " "
			<< (int)levelEnd.getPosition().x << "x" << (int)levelEnd.getPosition().y << std::endl;
		for (auto &e : recVec)
		{
			fout << "RectangleShape " << (int)e.getPosition().x << "x" << (int)e.getPosition().y << " " << (int)e.getSize().x << "x" << (int)e.getSize().y << " "
				<< "255,255,255" << std::endl;
		}
		for (auto &e : spikeVec)
		{
			fout << "CircleShape " << (int)(e.shape.getPosition().x-e.shape.getGlobalBounds().width/2) << "x" << (int)(e.shape.getPosition().y - e.shape.getGlobalBounds().height / 2) << " " << (int)e.shape.getRadius() << ","
				<< (int)e.shape.getPointCount() << std::endl;
		}
	}
	else
		std::cout << "Blad zapisu pliku!" << std::endl;
}

EditorScreen::EditorScreen(sf::RenderWindow *window)
{
	this->window = window;

	currentShapeType = "rectangle";
	shape.setSize(sf::Vector2f(100, 100));
	levelStart.setSize(sf::Vector2f(30, 30));
	levelEnd.setSize(sf::Vector2f(15, 60));

	levelStart.setFillColor(sf::Color(0, 255, 0, 128));
	levelEnd.setFillColor(sf::Color(0, 0, 255, 128));

	isLevelStartPlaced = isLevelEndPlaced = 0;

	spike.shape.setPointCount(3);
	spike.shape.setRadius(20);
	spike.shape.setFillColor(sf::Color(200, 200, 200));
	spike.shape.setOrigin(sf::Vector2f(spike.shape.getGlobalBounds().width / 2, spike.shape.getGlobalBounds().height / 2));

	wasLeftMouseClicked = 0;
	wasRightMouseClicked = 0;
	wasDeleteClicked = 0;
	wasDownPressed = 0;
	wasUpPressed = 0;
	spikeSeriesSet = 0;
	previousMousePosition = sf::Mouse::getPosition();
}


EditorScreen::~EditorScreen()
{
}

int EditorScreen::run()
{
	recVec.clear();
	startDelta.restart();

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
					return 0;
			}
		}
		checkCurrentState();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (currentShapeType == "rectangle")
		{
			addRectangleShape();
			removeRectangleShape();
			transformRectangleShape();
			shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x - shape.getGlobalBounds().width / 2, sf::Mouse::getPosition(*window).y - shape.getGlobalBounds().height / 2));
		}
		else
			shape.setPosition(sf::Vector2f(-shape.getGlobalBounds().width, -shape.getGlobalBounds().height));

		if (currentShapeType == "spike")
		{
			addSpikeShape();
			removeSpikeShape();
			rotateSpike();
			spike.shape.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
		}
		else
			spike.shape.setPosition(sf::Vector2f(-spike.shape.getGlobalBounds().width, -spike.shape.getGlobalBounds().height));

		if (currentShapeType == "levelStart")
		{
			if(!isLevelStartPlaced)
				levelStart.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x - levelStart.getGlobalBounds().width / 2, sf::Mouse::getPosition(*window).y - levelStart.getGlobalBounds().height / 2));
			addStartShape();
			removeStartShape();
		}
		else if(!isLevelStartPlaced)
			levelStart.setPosition(sf::Vector2f(-levelStart.getGlobalBounds().width, -levelStart.getGlobalBounds().height));
		
		if (currentShapeType == "levelEnd")
		{
			if (!isLevelEndPlaced)
				levelEnd.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x - levelEnd.getGlobalBounds().width / 2, sf::Mouse::getPosition(*window).y - levelEnd.getGlobalBounds().height / 2));
			addEndShape();
			removeEndShape();
		}
		else if (!isLevelEndPlaced)
			levelEnd.setPosition(sf::Vector2f(-levelEnd.getGlobalBounds().width, -levelEnd.getGlobalBounds().height));
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//shape.setFillColor(sf::Color::White);

		//TO DO - change view with mouse
		/*if (sf::Mouse::getPosition() != previousMousePosition && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			window->setView(window->getView().move(sf::Vector2f(sf::Mouse::getPosition().x - previousMousePosition.x, sf::Mouse::getPosition().y - previousMousePosition.y));
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sf::Font font;
			font.loadFromFile("fonts/homespun.ttf");
			std::string str;
			sf::Text text;
			std::getline(std::cin, str);
			saveFile(str);
		}

		window->clear();
		window->draw(shape);
		for (auto &e : recVec)
			window->draw(e);
		for (auto &e : spikeVec)
			window->draw(e.shape);
		window->draw(levelStart);
		window->draw(levelEnd);
		window->draw(spike.shape);
		window->display();
	};
	return 1;
}
