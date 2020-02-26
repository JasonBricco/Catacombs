#include "Stdafx.h"
#include "Generator.h"
#include "Generator.h"
#include "Player.h"
#include "Tiles.h"
#include "Chest.h"

template <typename T>
static void AddEntity(Room* room, int x, int y)
{
	T* entity = new T();
	entity->SetPosition(x, y);
	room->AddEntity(entity);
}

template <typename T>
static void AddRect(Room* room, int minX, int minY, int maxX, int maxY)
{
	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
			AddEntity<T>(room, x, y);
	}
}

static Room* CreateRoom(Level* level, int x, int y, bool doorDown)
{
	Room* room = level->GetOrCreateRoom(x, y);

	AddEntity<WallUpRight>(room, Room::Width - 2, 0);
	AddEntity<WallDownRight>(room, Room::Width - 2, Room::Height - 2);
	AddEntity<WallUpLeft>(room, 0, 0);
	AddEntity<WallDownLeft>(room, 0, Room::Height - 2);
	
	int doorP = Room::Width / 2;

	AddRect<WallUp>(room, 2, 0, doorP - 2, 0);
	AddRect<WallUp>(room, doorP + 2, 0, Room::Width - 3, 0);

	AddEntity<DoorUp>(room, doorP - 1, 0);

	if (doorDown)
	{
		AddRect<WallDown>(room, 2, Room::Height - 2, doorP - 2, Room::Height - 2);
		AddRect<WallDown>(room, doorP + 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

		AddEntity<DoorDown>(room, doorP - 1, Room::Height - 2);
	}
	else AddRect<WallDown>(room, 2, Room::Height - 2, Room::Width - 3, Room::Height - 2);

	AddRect<WallLeft>(room, 0, 2, 0, Room::Height - 3);
	AddRect<WallRight>(room, Room::Width - 2, 2, Room::Width - 2, Room::Height - 3);

	AddRect<FloorTile>(room, 2, 2, Room::Width - 3, Room::Height - 3);

	return room;
}

void LevelGenerator::Build(Level* level)
{
	Room* startRoom = CreateRoom(level, 0, 0, false);

	for (int y = 1; y < 10; ++y)
		CreateRoom(level, 0, y, true);

	Player* player = new Player();
	Chest* chest = new Chest();

	chest->spawn(player);
	startRoom->AddEntity(chest);

	player->SetPosition(8, 5);
	startRoom->AddEntity(player);

	level->SetCurrentRoom(startRoom);
}
