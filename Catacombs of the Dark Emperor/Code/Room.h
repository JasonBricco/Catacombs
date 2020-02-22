#pragma once

#include "Entity.h"

class Room
{
	std::vector<Entity*> entities;

public:
	// Room size in world units (1 unit = 32 pixels).
	static constexpr int Width = 32;
	static constexpr int Height = 18;

	inline void AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	inline std::vector<Entity*>& GetEntities()
	{
		return entities;
	}

	void Update(Level* level, float elapsed);
	void Draw(sf::RenderWindow& window);
};
