#pragma once

#include "Level.h"
#include "Player.h"

// Base class for a level generator.
class Generator
{
	virtual void Build(Level*) {}
};

struct PathDirection
{
	DoorType doorType;
	int dir;
	int doorP;
};

struct BranchStart
{
	Vector2i start;
	Vector2i dir;
	PathDirection pd;
};

struct LevelGenerator : public Generator
{
	Player* player;

	Vector2iSet roomsAdded;

	// Stores the first room for each branching path.
	std::vector<BranchStart> branches;

	void Build(Level*) override;

private:
	void GeneratePath(Level* level, Vector2i start, Vector2i end, PathDirection prevDir, bool mainPath = false);
};
