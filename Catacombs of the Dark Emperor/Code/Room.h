#pragma once

#include "Entity.h"

class Room
{
	Vector2i pos;
	std::vector<Entity*> entities;

	int doors[4];

public:
	// Room size in world units (1 unit = 32 pixels).
	static constexpr int Width = 32;
	static constexpr int Height = 18;

	inline void SetPosition(int x, int y)
	{
		pos = Vector2i(x, y);
	}

	inline Vector2i GetPosition()
	{
		return pos;
	}

	inline void AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	inline void RemoveEntity(Entity* entity)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	}

	inline std::vector<Entity*>& GetEntities()
	{
		return entities;
	}

	inline void SetDoor(int dir, int loc)
	{
		doors[dir] = loc;
	}

	inline int* GetDoors()
	{
		return doors;
	}

	void Update(Level* level, float elapsed);
	void Draw(Renderer& rend);
};
