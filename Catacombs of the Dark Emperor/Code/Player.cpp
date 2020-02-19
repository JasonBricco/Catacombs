
#include "Stdafx.h"
#include "Player.h"


Player::Player()
{
	if (!texture.loadFromFile("Assets/hero-idle-front.png"))
		OutputDebugStringA("Failed to load player texture.");
	else sprite.setTexture(texture);
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(sf::Vector2(changeX, changeY));
	window.draw(sprite);
}

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
}

