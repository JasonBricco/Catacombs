#include "Stdafx.h"
#include "Generator.h"
#include "Generator.h"
#include "Player.h"
#include "Tiles.h"
#include "Chest.h"

static Room* CreateRoom(Level* level, int x, int y, bool* dirs, bool* prevDirs)
{
	Room* room = level->GetOrCreateRoom(x, y);

	// Add corner tiles.
	AddEntity<WallUpRight>(room, Room::Width - 2, 0);
	AddEntity<WallDownRight>(room, Room::Width - 2, Room::Height - 2);
	AddEntity<WallUpLeft>(room, 0, 0);
	AddEntity<WallDownLeft>(room, 0, Room::Height - 2);

	int doorX = Room::Width / 2;
	int doorY = Room::Height / 2;

	// Top row of walls.
	if (dirs[UP] || prevDirs[DOWN])
	{
		AddRect<WallUp>(room, 2, 0, doorX - 2, 0);
		AddRect<WallUp>(room, doorX + 2, 0, Room::Width - 3, 0);

		AddEntity<DoorUp>(room, doorX - 1, 0);

		// Add barriers so that some parts of the room sprite 
		// are solid. Barriers are invisible colliders.
		AddEntity<Barrier>(room, doorX - 1, 0, 0.6f, 2.0f);
		AddEntity<Barrier>(room, doorX + 1, 0, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else AddRect<WallUp>(room, 2, 0, Room::Width - 3, 0);

	// Add bottom row of walls.
	if (dirs[DOWN] || prevDirs[UP])
	{
		AddRect<WallDown>(room, 2, Room::Height - 2, doorX - 2, Room::Height - 2);
		AddRect<WallDown>(room, doorX + 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

		AddEntity<DoorDown>(room, doorX - 1, Room::Height - 2);

		AddEntity<Barrier>(room, doorX - 1, Room::Height - 2, 0.6f, 2.0f);
		AddEntity<Barrier>(room, doorX + 1, Room::Height - 2, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else AddRect<WallDown>(room, 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

	// Add left row of walls.
	if (dirs[LEFT] || prevDirs[RIGHT])
	{
		AddRect<WallLeft>(room, 0, 2, 0, doorY - 2);
		AddRect<WallLeft>(room, 0, doorY + 2, 0, Room::Height - 3);

		AddEntity<DoorLeft>(room, 0, doorY - 1);

		// TODO: Barriers.
	}
	else AddRect<WallLeft>(room, 0, 2, 0, Room::Height - 3);

	// Add right row of walls.
	if (dirs[RIGHT] || prevDirs[LEFT])
	{
		AddRect<WallRight>(room, Room::Width - 2, 2, Room::Width - 2, doorY - 2);
		AddRect<WallRight>(room, Room::Width - 2, doorY + 2, Room::Width - 2, Room::Height - 3);

		AddEntity<DoorRight>(room, Room::Width - 2, doorY - 1);

		// TODO: Barriers.
	}
	else AddRect<WallRight>(room, Room::Width - 2, 2, Room::Width - 2, Room::Height - 3);

	// Add floor tiles.
	AddRect<FloorTile>(room, 2, 2, Room::Width - 3, Room::Height - 3);

	return room;
}

void LevelGenerator::Build(Level* level)
{
	Player* player = new Player();

	// Store directions as vectors for convenience.
	Vector2i vecDirs[5];
	vecDirs[UP] = Vector2i(0, 1);
	vecDirs[DOWN] = Vector2i(0, -1);
	vecDirs[LEFT] = Vector2i(-1, 0);
	vecDirs[RIGHT] = Vector2i(1, 0);

	// The number of rooms away from the origin our ending
	// room can be in either axis.
	int radius = 5;

	Vector2i start = Vector2i(0, 0);

	// Ensure the room is at the edge of the area to consider.
	int x = randomInRange(0, 1) == 0 ? radius : randomInRange(-radius, radius);
	int y = x == radius ? randomInRange(-radius, radius) : radius;

	Vector2i end = Vector2i(x, y);
	
	bool initial = true;

	Vector2i cur = start;

	bool prevDirs[4] = {};

	// Loop until we reach the end room.
	// When we do, the loop will exit via a break.
	while (true)
	{
		int diffX = end.x - cur.x;
		int diffY = end.y - cur.y;

		bool dirs[4] = {};
		int choice = 0;

		if (cur != end)
		{
			dirs[UP] = diffY > 0;
			dirs[DOWN] = diffY < 0;
			dirs[LEFT] = diffX < 0;
			dirs[RIGHT] = diffX > 0;

			do { choice = randomInRange(0, 3); }
			while (!dirs[choice]);

			// Ensure only one direction is chosen.
			for (int i = 0; i < 4; ++i)
			{
				if (i != choice)
					dirs[i] = false;
			}
		}

		Room* room = CreateRoom(level, cur.x, cur.y, dirs, prevDirs);
		roomsAdded.insert(cur);

		// Copy current directions to the previous directions.
		memcpy(prevDirs, dirs, sizeof(dirs));

		if (initial)
		{
			player->SetPosition(8, 5);
			room->AddEntity(player);

			level->SetCurrentRoom(room);
			initial = false;
		}
		else
		{
			// 50% (for now) chance of spawning a red chest in this room.
			if (randomUnit() <= 0.9f)
			{
				Chest* chest = new Chest();

				chest->spawn(player, 1);
				room->AddEntity(chest);
			}
			// 10% (for now) chance of spawning a blue chest in this room.
			if (randomUnit() <= 0.9f)
			{
				Chest* chest = new Chest();

				chest->spawn(player, 2);
				room->AddEntity(chest);
			}
		}

		if (cur == end) break;
		else cur += vecDirs[choice];
	}
}
