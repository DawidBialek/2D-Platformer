#include "../include/stdafx.h"
#include "../include/Player.h"


void Player::resetPlayer()
{
	shape.setPosition(startingPosition);
	velocity.x = velocity.y = 0;
	playerTimer.restart();
}

Player::Player()
{
	shape.setSize(sf::Vector2f(30, 30));
	shape.setFillColor(sf::Color::Magenta);
	acceleration = 10;
	isJumping = 0;
	collisionLeft = collisionRight = 0;
	playerTimer.restart();
}


Player::~Player()
{
}

void Player::load(Level level)
{
	playerTimer.restart();
	shape.setPosition(level.levelStart.getPosition());
	startingPosition = shape.getPosition();
	velocity = sf::Vector2f(0, 0);
}
void Player::checkCollisions(std::vector<sf::RectangleShape> rectangleVector, std::vector<Spike> spikeVector, sf::Vector2f lowestRecPos)
{
	int i = 0;
	collisionLeft = 0;
	collisionRight = 0;
	isJumping = 1;
	for (auto &e : rectangleVector)
	{
		if (shape.getGlobalBounds().intersects(e.getGlobalBounds()))
		{
			//over
			if (previousPosition.y + shape.getGlobalBounds().height <= e.getPosition().y)
			{
				shape.move(sf::Vector2f(0, -1 * (shape.getPosition().y + shape.getGlobalBounds().height - e.getPosition().y)));
				velocity.y = 0;
				isJumping = 0;
			}
			//under
			if (previousPosition.y >= e.getPosition().y + e.getGlobalBounds().height)
			{
				shape.move(sf::Vector2f(0, -1 * (shape.getPosition().y - (e.getPosition().y + e.getGlobalBounds().height))));
				velocity.y = 0;
			}
			//left
			if (previousPosition.x + shape.getGlobalBounds().width <= e.getPosition().x)
			{
				shape.move(sf::Vector2f(-1 * (shape.getPosition().x + shape.getGlobalBounds().width - e.getPosition().x), 0));
				velocity.y -= velocity.x;
				velocity.x = 0;
				collisionLeft = 1;
			}
			//right
			if (previousPosition.x >= e.getPosition().x + e.getGlobalBounds().width)
			{
				shape.move(sf::Vector2f(-1 * (shape.getPosition().x - (e.getPosition().x + e.getGlobalBounds().width)), 0));
				velocity.y += velocity.x;
				velocity.x = 0;
				collisionRight = 1;
			}
		}
		i++;
	}
	if (shape.getPosition().y > lowestRecPos.y+shape.getGlobalBounds().height*3)
		resetPlayer();
	double sum1=0, sum2=0;
	int j = 0;
	for (auto &e : spikeVector)
	{
		//calculating area to see if bottom left or bottom right vertices collides with a spike
		sum1 = e.calculateArea(sf::Vector2f(shape.getPosition().x,shape.getPosition().y + shape.getGlobalBounds().height), e.vertices[0], e.vertices[1]) + e.calculateArea(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + shape.getGlobalBounds().height), e.vertices[1], e.vertices[2]) + e.calculateArea(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + shape.getGlobalBounds().height), e.vertices[2], e.vertices[0]);
		sum2 = e.calculateArea(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height), e.vertices[0], e.vertices[1]) + e.calculateArea(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height), e.vertices[1], e.vertices[2]) + e.calculateArea(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height), e.vertices[2], e.vertices[0]);
		//std::cout << "sum: " << sum1 << " e.area: " << e.area << e.calculateArea(shape.getPosition(), e.vertices[0], e.vertices[1]) << " " << e.calculateArea(shape.getPosition(), e.vertices[1], e.vertices[2]) << " " << e.calculateArea(shape.getPosition(), e.vertices[2], e.vertices[0]) << "\r";
		//std::cout << j << " " << sum1 << " " << sum2 << " " << e.area << std::endl;
		if(sum1 <= e.area || sum2 <= e.area)
			resetPlayer();
		j++;
	}
	previousPosition = shape.getPosition();
}
void Player::control(sf::Time time)
{
	previousPosition = shape.getPosition();

	//jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && isJumping == 0)
	{
		velocity.y = -105;
		isJumping = 1;

	}
	
	//moving left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && velocity.x > -10)
			velocity.x -= 0.8;
		else if (velocity.x > -6)
			velocity.x -= 0.4;
		else if (velocity.x < -6.1)
			velocity.x += 0.2;
		//std::cout << velocity.x << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && velocity.x < 10)
			velocity.x += 0.8;
		else if(velocity.x < 6)
			velocity.x += 0.4;
		else if (velocity.x > 6.1)
			velocity.x -= 0.2;
		//std::cout << velocity.x << std::endl;
	}
	
	//jumping from wall to the left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && collisionLeft ==1)
	{
		velocity.x = -12;
		velocity.y = -120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && collisionRight == 1)
	{
		velocity.x = 12;
		velocity.y = -120;
	}

	//moving player
	shape.move(sf::Vector2f(velocity.x*acceleration*time.asSeconds()*5, velocity.y*time.asSeconds()*5));
	
	//slowing player horizontally
	if (velocity.x > 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x -= 16 * time.asSeconds();

	if (velocity.x < 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x += 16 * time.asSeconds();
	
	//slowing player vertically
	if (velocity.y < 100)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) && velocity.y < 0)
			velocity.y += acceleration * time.asSeconds() * 16;
		else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && velocity.y < 0)
		{
			velocity.y += acceleration * time.asSeconds() * 160;
			if (velocity.y > 0)
				velocity.y = 0;
			/*if (velocity.y > 0)
				velocity.y = -1 * (velocity.y / 2);*/
			isJumping = 0;
		}
		else
			velocity.y += acceleration * time.asSeconds() * 16;
	}

	//zeroing player horizontal speed
	if (velocity.x < 0.4 && velocity.x > -0.4 && velocity.x != 0)
		velocity.x = 0;

}
