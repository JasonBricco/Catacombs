
#include "Stdafx.h"
#include "Player.h"
#include "Assets.h"

void Player::move(int x)
{
	if (x == 1)
	{
		changeY = changeY - speed;
	}
	else if (x == 2)
	{
		changeX = changeX - speed;
	}
	else if (x == 3)
	{
		changeY = changeY + speed;
	}
	else if (x == 4)
	{
		changeX = changeX + speed;
	}

	changeX = std::clamp(changeX, 0.0f, 992.0f);
	changeY = std::clamp(changeY, 0.0f, 544.0f);

	position = sf::Vector2f(changeX, changeY);
}

void Player::Update(float elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// 1 is for up
		move(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// 2 is for left
		move(2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// 3 is for down
		move(3);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// 4 is for right
		move(4);
	}
}
