#pragma once

#include "Entity.h"

class Room
{
	std::vector<Entity*> entities;

public:
	inline void AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void Update(float elapsed);
	void Draw(sf::RenderWindow& window);
};