#pragma once

#include "Level.h"
#include "Player.h"

// Base class for a level generator.
class Generator
{
	virtual void Build(Level*) {}
};

// Builds a single room, places the player in it,
// and sets it as the current room.
struct SingleRoomGenerator : public Generator
{
	void Build(Level*) override;
};

struct BasicGenerator : public Generator
{
	void Build(Level*) override;
};

struct LevelGenerator : public Generator
{
	Player* player;
	Vector2iSet roomsAdded;

	// Stores the first room for each branching path.
	std::vector<Vector2i> branches;

	void Build(Level*) override;

private:
	void GeneratePath(Level* level, Vector2i start, Vector2i end, bool mainPath = false);
};

template <typename T, typename... Args>
inline void AddEntity(Room* room, int x, int y, Args... args)
{
	T* entity = new T(args...);
	entity->SetPosition(x, y);
	room->AddEntity(entity);
}

template <typename T>
inline void AddRect(Room* room, int minX, int minY, int maxX, int maxY)
{
	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
			AddEntity<T>(room, x, y);
	}
}