#pragma once

#include "Entity.h"
#include "Utils.h"

enum class DoorType
{
	None,
	Normal,
	Stairs,
	Barred
};

struct RoomDoor
{
	int pos;
	DoorType type;
};

struct Room
{
	// Room size in world units (1 unit = 32 pixels).
	static constexpr int Width = 32;
	static constexpr int Height = 18;
	static constexpr int TileCount = Width * Height;

	static inline bool InBounds(int x, int y)
	{
		return x >= 0 && x < Room::Width&& y >= 0 && y < Room::Height;
	}

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

	template <typename T, typename... Args>
	inline void AddEntity(int x, int y, Args... args)
	{
		T* entity = new T(args...);
		entity->SetPosition(x, y);
		entities.push_back(entity);
	}

	template <typename T, typename... Args>
	inline void AddRect(int minX, int minY, int maxX, int maxY, Args... args)
	{
		for (int y = minY; y <= maxY; ++y)
		{
			for (int x = minX; x <= maxX; ++x)
				AddEntity<T>(x, y, args...);
		}
	}

	void RemoveEntity(Entity* entity);

	inline std::vector<Entity*>& GetEntities()
	{
		return entities;
	}

	inline void SetDoor(int dir, int loc, DoorType type)
	{
		doors[dir] = { loc, type };
	}

	inline RoomDoor* GetDoors()
	{
		return doors;
	}

	bool TrySetObstacle(int x, int y);
	
	inline bool ObstacleAt(int x, int y)
	{
		auto it = obstacles.find(Vector2i(x, y));
		return it != obstacles.end();
	}

	inline int* PathGrid()
	{
		return pathGrid;
	}

	void BuildPathGrid();
	void Update(Level* level, float elapsed);
	void Draw(Renderer& rend);

private:
	int pathGrid[Width * Height];
	std::vector<RectangleShape> debugPathRects;

	Vector2i pos;
	std::vector<Entity*> entities;

	// Stores obstacles in order to prevent
	// them from appearing at the same location in a room.
	Vector2iSet obstacles;

	RoomDoor doors[4];
};

typedef std::unordered_map<Vector2i, Room*, Vector2iHash, Vector2iCompare> RoomMap;
