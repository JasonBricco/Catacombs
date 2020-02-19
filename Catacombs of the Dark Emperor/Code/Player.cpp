
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
	sprite.setPosition(sf::Vector2(100.0f, 100.0f));
	window.draw(sprite);
}
