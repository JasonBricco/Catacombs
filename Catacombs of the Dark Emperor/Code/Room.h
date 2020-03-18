#pragma once

#include "Entity.h"
#include "Utils.h"

class Room
{
	Vector2i pos;
	std::vector<Entity*> entities;

	// Stores obstacles in order to prevent
	// them from appearing at the same location in a room.
	Vector2iSet obstacles;

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

	bool TrySetObstacle(int x, int y);
	
	inline bool ObstacleAt(int x, int y)
	{
		auto it = obstacles.find(Vector2i(x, y));
		return it != obstacles.end();
	}

	void Update(Level* level, float elapsed);
	void Draw(Renderer& rend);
};

typedef std::unordered_map<Vector2i, Room*, Vector2iHash, Vector2iCompare> RoomMap;
