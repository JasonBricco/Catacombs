#include "Stdafx.h"
#include "Generator.h"
#include "Player.h"
#include "Tiles.h"
#include "Chest.h"
#include "Enemies.h"

enum class RoomFeatures
{
	Rocks,
	Blocks
};

using BlockFunc = void(*)(Room* room);

static Vector2i RandomRoomPos()
{
	return Vector2i(randomInRange(3, Room::Width - 4), randomInRange(3, Room::Height - 4));
}

// Generates random blocks.
static void BlockPattern1(Room* room)
{
	int blockCount = randomInRange(2, 6);

	for (int i = 0; i < blockCount; i++)
	{
		int x = randomInRange(3, Room::Width - 4);
		int y = randomInRange(3, Room::Height - 4);

		if (room->TrySetObstacle(x, y))
			room->AddEntity<BlockTile>(x, y);
	}
}

// Generates a larger amount of random blocks.
static void BlockPattern2(Room* room)
{
	int blockCount = randomInRange(10, 25);

	for (int i = 0; i < blockCount; i++)
	{
		int x = randomInRange(3, Room::Width - 4);
		int y = randomInRange(3, Room::Height - 4);
		
		if (room->TrySetObstacle(x, y))
			room->AddEntity<BlockTile>(x, y);
	}
}

// Generates block walls.
static void BlockPattern3(Room* room)
{
	int count = randomInRange(2, 3);

	for (int i = 0; i < count; i++)
	{
		bool vertical = randomUnit() < 0.5f;

		int startX = randomInRange(3, 11);
		int startY = randomInRange(4, 7);

		if (vertical)
		{
			int dist = randomInRange(4, 8);

			for (int j = startY; j < startY + dist; j++)
			{
				if (room->TrySetObstacle(startX, j))
					room->AddEntity<BlockTile>(startX, j);
			}
		}
		else
		{
			int dist = randomInRange(8, 14);

			for (int j = startX; j < startX + dist; j++)
			{
				if (room->TrySetObstacle(j, startY))
					room->AddEntity<BlockTile>(j, startY);
			}
		}
	}
}

// Generates an X pattern.
static void BlockPattern4(Room* room)
{
	int y = Room::Height - 4;

	int start = randomInRange(4, 10);
	int end = start + randomInRange(7, 10);

	for (int x = start; x < end; ++x, --y)
	{
		if (room->TrySetObstacle(x, y))
			room->AddEntity<BlockTile>(x, y);

		if (room->TrySetObstacle(x, Room::Height - y))
			room->AddEntity<BlockTile>(x, Room::Height - y);

		if (room->TrySetObstacle(Room::Width - x, y))
			room->AddEntity<BlockTile>(Room::Width - x, y);

		if (room->TrySetObstacle(Room::Width - x, Room::Height - y))
			room->AddEntity<BlockTile>(Room::Width - x, Room::Height - y);
	}
}

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
			room->AddEntity<PotTile>(x, side);
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
			room->AddEntity<PotTile>(side, y);
	}
}

static void SpawnEnemies(Room* room)
{
	int amt = randomInRange(1, 3);

	for (int i = 0; i < amt; ++i)
	{
		Vector2i p = RandomRoomPos();

		if (room->TrySetObstacle(p.x, p.y))
			room->AddEntity(new Wolf(p.x, p.y));
	}
}

static void FillRoom(Room* room)
{
	RoomFeatures features = randomInRange(0, 2) == 0 ? RoomFeatures::Blocks : RoomFeatures::Rocks;
	bool addPots = false;

	if (features == RoomFeatures::Rocks)
		addPots = randomInRange(0, 2) == 0;

	int offset = randomInRange(0, 2) == 0 ? 0 : 4;

	// Add corner tiles.
	room->AddEntity<WallCorner>(Room::Width - 2, 0, UP_RIGHT + offset);
	room->AddEntity<WallCorner>(Room::Width - 2, Room::Height - 2, DOWN_RIGHT + offset);
	room->AddEntity<WallCorner>(0, 0, UP_LEFT + offset);
	room->AddEntity<WallCorner>(0, Room::Height - 2, DOWN_LEFT + offset);

	RoomDoor* doors = room->GetDoors();

	// Top row of walls.
	if (doors[UP].pos > 0)
	{
		int doorX = doors[UP].pos;

		room->AddRect<WallUp>(2, 0, doorX - 2, 0);
		room->AddRect<WallUp>(doorX + 2, 0, Room::Width - 3, 0);

		if (doors[UP].type == DoorType::Stairs)
			room->AddEntity<DoorStairs>(doorX - 1, 0, UP);
		else
		{
			if (doors[UP].type == DoorType::Barred)
				room->AddEntity<BarredDoor>(doorX - 1, 0, UP);
			else room->AddEntity<DoorUp>(doorX - 1, 0);
		}

		// Add barriers so that some parts of the room sprite 
		// are solid. Barriers are invisible colliders.
		room->AddEntity<Barrier>(doorX - 1, 0, 0.6f, 2.0f);
		room->AddEntity<Barrier>(doorX + 1, 0, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else
	{
		room->AddRect<WallUp>(2, 0, Room::Width - 3, 0);
		if (addPots) AddPotsX(room, 2);
	}

	// Add bottom row of walls.
	if (doors[DOWN].pos > 0)
	{
		int doorX = doors[DOWN].pos;

		room->AddRect<WallDown>(2, Room::Height - 2, doorX - 2, Room::Height - 2);
		room->AddRect<WallDown>(doorX + 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

		if (doors[DOWN].type == DoorType::Stairs)
			room->AddEntity<DoorStairs>(doorX - 1, Room::Height - 2, DOWN);
		else
		{
			if (doors[DOWN].type == DoorType::Barred)
				room->AddEntity<BarredDoor>(doorX - 1, Room::Height - 2, DOWN);
			else room->AddEntity<DoorDown>(doorX - 1, Room::Height - 2);
		}

		room->AddEntity<Barrier>(doorX - 1, Room::Height - 2, 0.6f, 2.0f);
		room->AddEntity<Barrier>(doorX + 1, Room::Height - 2, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else
	{
		room->AddRect<WallDown>(2, Room::Height - 2, Room::Width - 3, Room::Height - 2);
		if (addPots) AddPotsX(room, Room::Height - 3);
	}

	// Add left row of walls.
	if (doors[LEFT].pos > 0)
	{
		int doorY = doors[LEFT].pos;

		room->AddRect<WallLeft>(0, 2, 0, doorY - 2);
		room->AddRect<WallLeft>(0, doorY + 2, 0, Room::Height - 3);

		room->AddEntity<DoorLeft>(0, doorY - 1);
		room->AddEntity<Barrier>(0, doorY - 1, 2.0f, 0.6f);
		room->AddEntity<Barrier>(0, doorY + 1, 2.0f, 0.6f, 0.0f, 0.4f);
	}
	else
	{
		room->AddRect<WallLeft>(0, 2, 0, Room::Height - 3);
		if (addPots) AddPotsY(room, 2);
	}

	// Add right row of walls.
	if (doors[RIGHT].pos)
	{
		int doorY = doors[RIGHT].pos;

		room->AddRect<WallRight>(Room::Width - 2, 2, Room::Width - 2, doorY - 2);
		room->AddRect<WallRight>(Room::Width - 2, doorY + 2, Room::Width - 2, Room::Height - 3);

		room->AddEntity<DoorRight>(Room::Width - 2, doorY - 1);
		room->AddEntity<Barrier>(Room::Width - 2, doorY - 1, 2.0f, 0.6f);
		room->AddEntity<Barrier>(Room::Width - 2, doorY + 1, 2.0f, 0.6f, 0.0f, 0.4f);
	}
	else
	{
		room->AddRect<WallRight>(Room::Width - 2, 2, Room::Width - 2, Room::Height - 3);
		if (addPots) AddPotsY(room, Room::Width - 3);
	}

	// Add floor tiles.
	room->AddRect<FloorTile>(2, 2, Room::Width - 3, Room::Height - 3);

	SpawnEnemies(room);

	if (features == RoomFeatures::Rocks)
	{
		int rockCount = randomInRange(0, 5);

		for (int i = 0; i < rockCount; ++i)
		{
			Vector2i p = RandomRoomPos();

			if (room->TrySetObstacle(p.x, p.y))
				room->AddEntity<RocksTile>(p.x, p.y);
		}
	}
	else if (features == RoomFeatures::Blocks)
	{
		BlockFunc funcs[4] = { BlockPattern1, BlockPattern2, BlockPattern3, BlockPattern4 };

		int pattern = randomInRange(0, 3);
		funcs[pattern](room);
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

	bool openUp = dirs[UP].doorType != DoorType::None;
	bool openDown = dirs[DOWN].doorType != DoorType::None;
	bool openLeft = dirs[LEFT].doorType != DoorType::None;
	bool openRight = dirs[RIGHT].doorType != DoorType::None;

	if (openUp || prevDir.dir == DOWN)
	{
		int doorX = openUp ? dirs[UP].doorP : prevDir.doorP;
		room->SetDoor(UP, doorX, dirs[UP].doorType);
	}

	if (openDown || prevDir.dir == UP)
	{
		int doorX = openDown ? dirs[DOWN].doorP : prevDir.doorP;
		room->SetDoor(DOWN, doorX, dirs[DOWN].doorType);
	}

	if (openLeft || prevDir.dir == RIGHT)
	{
		int doorY = openLeft ? dirs[LEFT].doorP : prevDir.doorP;
		room->SetDoor(LEFT, doorY, dirs[LEFT].doorType);
	}

	if (openRight || prevDir.dir == LEFT)
	{
		int doorY = openRight ? dirs[RIGHT].doorP : prevDir.doorP;
		room->SetDoor(RIGHT, doorY, dirs[RIGHT].doorType);
	}

	return room;
}

void LevelGenerator::SpawnPlayer()
{
	float spawnX, spawnY;
	int tryX, tryY;

	if (spawnPrevDir.dir == UP)
	{
		spawnX = Room::Width / 2 - 0.5f;
		spawnY = Room::Height - 4 - 0.25f;
	}
	else if (spawnPrevDir.dir == DOWN)
	{
		spawnX = Room::Width / 2 - 0.5f;
		spawnY = 1.5f;
	}
	else
	{
		do
		{
			tryX = randomInRange(4, 8);
			tryY = randomInRange(4, 8);
		} while (spawnRoom->ObstacleAt(tryX, tryY));

		Vector2f size = player->GetSize();

		spawnX = (float)tryX - 0.5f;
		spawnY = (float)tryY - 1.0f;
	}

	player->SetPosition(spawnX, spawnY);
	spawnRoom->AddEntity(player);
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
			dirs[UP] = { diffY > 0 ? DoorType::Normal : DoorType::None, UP };
			dirs[DOWN] = { diffY < 0 ? DoorType::Normal : DoorType::None, DOWN };
			dirs[LEFT] = { diffX < 0 ? DoorType::Normal : DoorType::None, LEFT };
			dirs[RIGHT] = { diffX > 0 ? DoorType::Normal : DoorType::None, RIGHT };

			int tries = 32;
			bool validDir = false;

			do
			{
				choice = randomInRange(0, 3);

				Vector2i nextP = cur + vecDirs[choice];
				auto it = roomsAdded.find(nextP);

				// The main path normally cannot generate in the direction 
				// we came from. However, if we're generating a new level, 
				// we could try to generate in the direction we came.
				bool cameFrom = prevDir.dir == GetOppositeDir(choice);

				if (dirs[choice].doorType == DoorType::Normal && it == roomsAdded.end() && !cameFrom)
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
					dirs[i].doorType = DoorType::None;
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
				if (dirs[dir].doorType == DoorType::None && prevDir.dir != GetOppositeDir(dir))
				{
					BranchStart branch = { cur, vecDirs[dir], dirs[dir] };
					branches.push_back(branch);
					dirs[dir].doorType = DoorType::Normal;
				}
			}
		}

		bool pathEnd = cur == end || noValidChoices;

		if (mainPath)
		{
			// Generate stairs going down to a new level
			// at the end of the main path.
			if (pathEnd)
			{
				int dir = UP;

				if (prevDir.dir == DOWN)
					dir = DOWN;

				dirs[dir].doorType = DoorType::Stairs;
				dirs[dir].doorP = randomInRange(4, Room::Width - 5);
			}

			if (initial && (prevDir.dir == DOWN || prevDir.dir == UP))
			{
				int opp = GetOppositeDir(prevDir.dir);
				dirs[opp].doorType = DoorType::Barred;
				dirs[opp].doorP = Room::Width / 2;
			}
		}

		Room* room = CreateRoom(level, cur.x, cur.y, dirs, prevDir);
		roomsAdded.insert(cur);

		if (initial)
		{
			if (mainPath)
			{
				spawnRoom = room;
				spawnPrevDir = prevDir;
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

					if (room->TrySetObstacle(x, y))
					{
						Chest* chest = new Chest();
						chest->spawn(player, 1, x, y);
						room->AddEntity(chest);
					}
				}
			}
		}

		// Blue chests can spawn only in end of path rooms.
		if (pathEnd)
		{
			if (randomUnit() <= 0.75f)
			{
				int x = randomInRange(3, Room::Width - 4);
				int y = randomInRange(3, Room::Height - 4);

				if (room->TrySetObstacle(x, y))
				{
					Chest* chest = new Chest();
					chest->spawn(player, 2, x, y);
					room->AddEntity(chest);
				}
			}

			break;
		}
		else cur += vecDirs[choice];

		prevDir = dirs[choice];
	}
}

void LevelGenerator::Build(Level* level)
{
	GameState& state = getGameState();

	if (!state.newLevel)
		player = new Player();

	// The number of rooms away from the origin our ending
	// room can be in either axis.
	int radius = 5;

	Vector2i start = Vector2i(0, 0);

	// Ensure the room is at the edge of the area to consider.
	int x = randomInRange(0, 1) == 0 ? radius : randomInRange(-radius, radius);
	int y = x == radius ? randomInRange(-radius, radius) : radius;

	Vector2i end = Vector2i(x, y);

	PathDirection initpd;

	if (state.newLevel)
		initpd = { DoorType::None, state.newLevelPrevDir, 0 };
	else initpd = { DoorType::None, -1, 0 };

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
			room->SetDoor(branch.pd.dir, 0, DoorType::None);
		}
	}

	FillRooms(level);
	SpawnPlayer();

	branches.clear();
	roomsAdded.clear();
}
