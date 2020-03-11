#include "Stdafx.h"
#include "Generator.h"
#include "Generator.h"
#include "Player.h"
#include "Tiles.h"
#include "Chest.h"

// Stores obstacles in order to prevent
// them from appearing at the same location in a room.
static Vector2iSet obstacles;

static void AddPotsX(Room* room, int side)
{
	// Weights for random generation to ensure pots are more likely toward corners.
	// The hardcoding is a bit janky, but it works for the moment.
	float weights[28] =
	{
		0.95f, 0.9f, 0.85f, 0.8f, 0.75f, 0.65f, 0.55f, 0.45f, 0.3f, 0.2f, 0.15f, 0.1f, 0.05f, 0.02f,
		0.02f, 0.05f, 0.1f, 0.15f, 0.2f, 0.3f, 0.45f, 0.55f, 0.65f, 0.75f, 0.8f, 0.85f, 0.9f, 0.95f
	};

	for (int x = 2; x < Room::Width - 2; ++x)
	{
		if (randomUnit() <= weights[x - 2])
			AddEntity<PotTile>(room, x, side);
	}
}

static void AddPotsY(Room* room, int side)
{
	float weights[14] =
	{
		0.95f, 0.9f, 0.8f, 0.7f, 0.5f, 0.3f, 0.1f,
		0.1f, 0.3f, 0.5f, 0.7f, 0.8f, 0.9f, 0.95f
	};

	for (int y = 2; y < Room::Height - 2; ++y)
	{
		if (randomUnit() <= weights[y - 2])
			AddEntity<PotTile>(room, side, y);
	}
}

static void FillRoom(Room* room)
{
	bool addPots = randomInRange(0, 2) == 0;

	int offset = randomInRange(0, 2) == 0 ? 0 : 4;

	// Add corner tiles.
	AddEntity<WallCorner>(room, Room::Width - 2, 0, UP_RIGHT + offset);
	AddEntity<WallCorner>(room, Room::Width - 2, Room::Height - 2, DOWN_RIGHT + offset);
	AddEntity<WallCorner>(room, 0, 0, UP_LEFT + offset);
	AddEntity<WallCorner>(room, 0, Room::Height - 2, DOWN_LEFT + offset);

	int* doors = room->GetDoors();

	// Top row of walls.
	if (doors[UP] > 0)
	{
		int doorX = doors[UP];

		AddRect<WallUp>(room, 2, 0, doorX - 2, 0);
		AddRect<WallUp>(room, doorX + 2, 0, Room::Width - 3, 0);

		AddEntity<DoorUp>(room, doorX - 1, 0);

		// Add barriers so that some parts of the room sprite 
		// are solid. Barriers are invisible colliders.
		AddEntity<Barrier>(room, doorX - 1, 0, 0.6f, 2.0f);
		AddEntity<Barrier>(room, doorX + 1, 0, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else
	{
		AddRect<WallUp>(room, 2, 0, Room::Width - 3, 0);
		if (addPots) AddPotsX(room, 2);
	}

	// Add bottom row of walls.
	if (doors[DOWN] > 0)
	{
		int doorX = doors[DOWN];

		AddRect<WallDown>(room, 2, Room::Height - 2, doorX - 2, Room::Height - 2);
		AddRect<WallDown>(room, doorX + 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

		AddEntity<DoorDown>(room, doors[DOWN] - 1, Room::Height - 2);
		AddEntity<Barrier>(room, doors[DOWN] - 1, Room::Height - 2, 0.6f, 2.0f);
		AddEntity<Barrier>(room, doors[DOWN] + 1, Room::Height - 2, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else
	{
		AddRect<WallDown>(room, 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);
		if (addPots) AddPotsX(room, Room::Height - 3);
	}

	// Add left row of walls.
	if (doors[LEFT] > 0)
	{
		int doorY = doors[LEFT];

		AddRect<WallLeft>(room, 0, 2, 0, doorY - 2);
		AddRect<WallLeft>(room, 0, doorY + 2, 0, Room::Height - 3);

		AddEntity<DoorLeft>(room, 0, doors[LEFT] - 1);
		// TODO: Barriers.
	}
	else
	{
		AddRect<WallLeft>(room, 0, 2, 0, Room::Height - 3);
		if (addPots) AddPotsY(room, 2);
	}

	// Add right row of walls.
	if (doors[RIGHT])
	{
		int doorY = doors[RIGHT];

		AddRect<WallRight>(room, Room::Width - 2, 2, Room::Width - 2, doorY - 2);
		AddRect<WallRight>(room, Room::Width - 2, doorY + 2, Room::Width - 2, Room::Height - 3);

		AddEntity<DoorRight>(room, Room::Width - 2, doors[RIGHT] - 1);
		// TODO: Barriers.
	}
	else
	{
		AddRect<WallRight>(room, Room::Width - 2, 2, Room::Width - 2, Room::Height - 3);
		if (addPots) AddPotsY(room, Room::Width - 3);
	}

	// Add floor tiles.
	AddRect<FloorTile>(room, 2, 2, Room::Width - 3, Room::Height - 3);

	int rockCount = randomInRange(0, 5);

	for (int i = 0; i < rockCount; ++i)
	{
		Vector2i p = Vector2i(randomInRange(3, Room::Width - 4), randomInRange(3, Room::Height - 4));

		if (obstacles.find(p) == obstacles.end())
		{
			AddEntity<RocksTile>(room, p.x, p.y);
			obstacles.insert(p);
		}
	}
}

// Add the doors in a deferred fashion so that adjustments can be made
// along the way based on how paths generate.
static void FillRooms(Level* level)
{
	for (auto pair : level->GetRooms())
	{
		Room* room = pair.second;
		FillRoom(room);
	}
}

// Creates a room and decides which doors should be initially open for it.
static Room* CreateRoom(Level* level, int x, int y, PathDirection* dirs, PathDirection prevDir)
{
	Room* room = level->GetOrCreateRoom(x, y);

	if (dirs[UP].open || prevDir.dir == DOWN)
	{
		int doorX = dirs[UP].open ? dirs[UP].doorP : prevDir.doorP;
		room->SetDoor(UP, doorX);
	}

	if (dirs[DOWN].open || prevDir.dir == UP)
	{
		int doorX = dirs[DOWN].open ? dirs[DOWN].doorP : prevDir.doorP;
		room->SetDoor(DOWN, doorX);
	}

	if (dirs[LEFT].open || prevDir.dir == RIGHT)
	{
		int doorY = dirs[LEFT].open ? dirs[LEFT].doorP : prevDir.doorP;
		room->SetDoor(LEFT, doorY);
	}

	if (dirs[RIGHT].open || prevDir.dir == LEFT)
	{
		int doorY = dirs[RIGHT].open ? dirs[RIGHT].doorP : prevDir.doorP;
		room->SetDoor(RIGHT, doorY);
	}

	return room;
}

void LevelGenerator::GeneratePath(Level* level, Vector2i start, Vector2i end, PathDirection prevDir, bool mainPath)
{
	// Store directions as vectors for convenience.
	Vector2i vecDirs[5];
	vecDirs[UP] = Vector2i(0, 1);
	vecDirs[DOWN] = Vector2i(0, -1);
	vecDirs[LEFT] = Vector2i(-1, 0);
	vecDirs[RIGHT] = Vector2i(1, 0);

	Vector2i cur = start;

	bool initial = true;
	Room* initialRoom = nullptr;

	// Loop until we reach the end room.
	// When we do, the loop will exit via a break.
	while (true)
	{
		int diffX = end.x - cur.x;
		int diffY = end.y - cur.y;

		PathDirection dirs[4] = {};
		int choice = 0;
		bool noValidChoices = false;

		if (cur != end)
		{
			dirs[UP] = { diffY > 0, UP };
			dirs[DOWN] = { diffY < 0, DOWN };
			dirs[LEFT] = { diffX < 0, LEFT };
			dirs[RIGHT] = { diffX > 0, RIGHT };

			int tries = 32;
			bool validDir = false;

			do
			{
				choice = randomInRange(0, 3);

				Vector2i nextP = cur + vecDirs[choice];
				auto it = roomsAdded.find(nextP);

				if (dirs[choice].open && it == roomsAdded.end())
					validDir = true;

				// Stop if we tried too many times.
				// Assume there's no possible direction to go.
				if (--tries == 0)
				{
					noValidChoices = true;
					break;
				}
			} 
			while (!validDir);

			// Ensure only one direction is chosen.
			for (int i = 0; i < 4; ++i)
			{
				// Leave our choice open and close the rest. 
				// If we found no possible directions, make sure
				// all directions are closed regardless.
				if (i != choice || noValidChoices)
					dirs[i].open = false;
			}

			// Select random door positions for each direction.
			// I set them for directions that aren't open as well
			// so that we'll have a valid position if we open the
			// door later (for example from creating a branching path).
			for (PathDirection& pd : dirs)
			{
				if (pd.dir == UP || pd.dir == DOWN)
					pd.doorP = randomInRange(4, Room::Width - 5);
				else pd.doorP = randomInRange(4, Room::Height - 5);
			}

			if (mainPath && randomInRange(0, 2) == 0)
			{
				int dir = randomInRange(0, 3);

				// Don't generate a branching path in the direction
				// we're already going on the main path, or in the
				// direction we came from.
				if (!dirs[dir].open && prevDir.dir != GetOppositeDir(dir))
				{
					BranchStart branch = { cur, vecDirs[dir], dirs[dir] };
					branches.push_back(branch);
					dirs[dir].open = true;
				}
			}
		}

		obstacles.clear();

		Room* room = CreateRoom(level, cur.x, cur.y, dirs, prevDir);
		roomsAdded.insert(cur);

		prevDir = dirs[choice];

		if (initial)
		{
			if (mainPath)
			{
				player->SetPosition(8, 5);
				room->AddEntity(player);

				level->SetCurrentRoom(room);
			}

			initialRoom = room;
			initial = false;
		}
		else
		{
			// Red chests can spawn in any room except
			// the end of path rooms.
			if (cur != end && !noValidChoices)
			{
				// 35% (for now) chance of spawning a red chest in this room.
				if (randomUnit() <= 0.35f)
				{
					int x = randomInRange(3, Room::Width - 4);
					int y = randomInRange(3, Room::Height - 4);

					if (obstacles.find(Vector2i(x, y)) == obstacles.end())
					{
						Chest* chest = new Chest();
						chest->spawn(player, 1, x, y);
						room->AddEntity(chest);
					}
				}
			}
		}

		// Blue chests can spawn only in end of path rooms.
		if (cur == end || noValidChoices)
		{
			if (randomUnit() <= 0.75f)
			{
				int x = randomInRange(3, Room::Width - 4);
				int y = randomInRange(3, Room::Height - 4);

				if (obstacles.find(Vector2i(x, y)) == obstacles.end())
				{
					Chest* chest = new Chest();

					chest->spawn(player, 2, x, y);
					room->AddEntity(chest);
				}
			}

			break;
		}
		else cur += vecDirs[choice];
	}
}

void LevelGenerator::Build(Level* level)
{
	player = new Player();

	// The number of rooms away from the origin our ending
	// room can be in either axis.
	int radius = 5;

	Vector2i start = Vector2i(0, 0);

	// Ensure the room is at the edge of the area to consider.
	int x = randomInRange(0, 1) == 0 ? radius : randomInRange(-radius, radius);
	int y = x == radius ? randomInRange(-radius, radius) : radius;

	Vector2i end = Vector2i(x, y);

	PathDirection initpd = { false, -1, {} };
	GeneratePath(level, start, end, initpd, true);

	for (BranchStart branch : branches)
	{
		do
		{
			int endX = randomInRange(-radius, radius);
			int endY = randomInRange(-radius, radius);

			end = Vector2i(endX, endY);
		} 
		while (roomsAdded.find(end) != roomsAdded.end());

		// Make sure the previous direction is set for the
		// first room of the path, so it connects back
		// to the main path.
		start = branch.start + branch.dir;

		if (roomsAdded.find(start) == roomsAdded.end())
			GeneratePath(level, start, end, branch.pd, false);
		else
		{
			// Remove the door that was added to enter this branch, 
			// this branch can't be made.
			Room* room = level->GetRoom(branch.start);
			room->SetDoor(branch.pd.dir, 0);
		}
	}

	FillRooms(level);
}
