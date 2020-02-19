#pragma once

class Player
{
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Player();

	void Draw(sf::RenderWindow& window);
};