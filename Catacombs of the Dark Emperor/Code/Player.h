#pragma once

class Player
{
	sf::Texture texture;
	sf::Sprite sprite;
	float changeX = 100.0f;
	float changeY = 100.0f;
	float speed = 4.0f;

public:
	Player();

	void Draw(sf::RenderWindow& window);

	void move(int x);
};