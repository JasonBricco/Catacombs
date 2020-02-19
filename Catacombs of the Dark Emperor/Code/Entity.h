#pragma once

class Entity
{
	sf::Sprite sprite;

protected:
	sf::Vector2f position;

public:
	Entity(std::string name);

	inline void SetPosition(float x, float y)
	{
		position = sf::Vector2f(x, y);
	}

	virtual void Update(float) {}
	void Draw(sf::RenderWindow& window);
};