#include "Stdafx.h"
#include "Generator.h"
#include "Generator.h"
#include "Player.h"
#include "Tiles.h"
#include "Chest.h"

static Room* CreateRoom(Level* level, int x, int y, int& doorP, bool last = false)
{
	Room* room = level->GetOrCreateRoom(x, y);

	// Add corner tiles.
	AddEntity<WallUpRight>(room, Room::Width - 2, 0);
	AddEntity<WallDownRight>(room, Room::Width - 2, Room::Height - 2);
	AddEntity<WallUpLeft>(room, 0, 0);
	AddEntity<WallDownLeft>(room, 0, Room::Height - 2);
	
	int newDoorP = 0;

	// Add top row of walls. Add a door if this isn't the last room.
	if (!last)
	{
		newDoorP = randomInRange(5, Room::Width - 6);

		AddRect<WallUp>(room, 2, 0, newDoorP - 2, 0);
		AddRect<WallUp>(room, newDoorP + 2, 0, Room::Width - 3, 0);

		AddEntity<DoorUp>(room, newDoorP - 1, 0);

		// Add barriers so that some parts of the room sprite 
		// are solid. Barriers are invisible colliders.
		AddEntity<Barrier>(room, newDoorP - 1, 0, 0.6f, 2.0f);
		AddEntity<Barrier>(room, newDoorP + 1, 0, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else AddRect<WallUp>(room, 2, 0, Room::Width - 3, 0);

	// Add a row of bottom walls. As long as we have a previous door
	// position, we must put a door going back down to match it.
	if (doorP != -1)
	{
		AddRect<WallDown>(room, 2, Room::Height - 2, doorP - 2, Room::Height - 2);
		AddRect<WallDown>(room, doorP + 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

		AddEntity<DoorDown>(room, doorP - 1, Room::Height - 2);

		AddEntity<Barrier>(room, newDoorP - 1, Room::Height - 2, 0.6f, 2.0f);
		AddEntity<Barrier>(room, newDoorP + 1, Room::Height - 2, 0.6f, 2.0f, 0.4f, 0.0f);
	}
	else AddRect<WallDown>(room, 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

	doorP = newDoorP;

	// Add the left and right wall columns.
	AddRect<WallLeft>(room, 0, 2, 0, Room::Height - 3);
	AddRect<WallRight>(room, Room::Width - 2, 2, Room::Width - 2, Room::Height - 3);

	// Add floor tiles.
	AddRect<FloorTile>(room, 2, 2, Room::Width - 3, Room::Height - 3);

	return room;
}

void BasicGenerator::Build(Level* level)
{
	Player* player = new Player();

	int doorP = -1;
	Room* startRoom = CreateRoom(level, 0, 0, doorP);

	int roomCount = 5;

	for (int y = 1; y < roomCount; ++y)
	{
		Room* room = CreateRoom(level, 0, y, doorP, y == roomCount - 1);

		// 50% (for now) chance of spawning a chest in this room.
		if (randomUnit() <= 0.5f)
		{
			Chest* chest = new Chest();

			chest->spawn(player, 1);
			room->AddEntity(chest);
		}
	}

	player->SetPosition(8, 5);
	startRoom->AddEntity(player);

	level->SetCurrentRoom(startRoom);
}
