
#include "Stdafx.h"
#include "Generator.h"
#include "Player.h"
#include "Tiles.h"
#include "Chest.h"

void SingleRoomGenerator::Build(Level* level)
{
	Room* room = level->GetOrCreateRoom(0, 0);

	level->SetCurrentRoom(room);

	WallUpRight* upRight = new WallUpRight();
	WallDownRight* downRight = new WallDownRight();
	WallUpLeft* upLeft = new WallUpLeft();
	WallDownLeft* downLeft = new WallDownLeft();

	upRight->SetPosition(Room::Width - 2, 0);
	downRight->SetPosition(Room::Width - 2, Room::Height - 2);
	upLeft->SetPosition(0, 0);
	downLeft->SetPosition(0, Room::Height - 2);

	room->AddEntity(upRight);
	room->AddEntity(downRight);
	room->AddEntity(upLeft);
	room->AddEntity(downLeft);

	for (int x = 2; x < Room::Width - 2; ++x)
	{
		WallUp* wallUp = new WallUp();
		wallUp->SetPosition(x, 0);
		room->AddEntity(wallUp);

		WallDown* wallDown = new WallDown();
		wallDown->SetPosition(x, Room::Height - 2);
		room->AddEntity(wallDown);
	}

	for (int y = 2; y < Room::Height - 2; ++y)
	{
		WallLeft* wallLeft = new WallLeft();
		wallLeft->SetPosition(0, y);
		room->AddEntity(wallLeft);

		WallRight* wallRight = new WallRight();
		wallRight->SetPosition(Room::Width - 2, y);
		room->AddEntity(wallRight);
	}

	for (int y = 2; y < Room::Height - 2; ++y)
	{
		for (int x = 2; x < Room::Width - 2; ++x)
		{
			FloorTile* tile = new FloorTile();
			tile->SetPosition(x, y);
			room->AddEntity(tile);
		}
	}

	Player* player = new Player();
	Chest* chest = new Chest();

	chest->spawn(player);
	room->AddEntity(chest);

	player->SetPosition(8, 5);
	room->AddEntity(player);
}
