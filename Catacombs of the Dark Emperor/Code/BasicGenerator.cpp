
#include "Stdafx.h"
#include "Generator.h"
#include "Player.h"

void BasicGenerator::Build(Level* level)
{
	Room* room = level->GetOrCreateRoom(0, 0);

	Player* player = new Player();
	
	player->SetPosition(100.0f, 100.0f);

	level->SetCurrentRoom(room);

	WallUpRight* upRight = new WallUpRight();
	WallDownRight* downRight = new WallDownRight();
	WallUpLeft* upLeft = new WallUpLeft();
	WallDownLeft* downLeft = new WallDownLeft();

	upRight->SetPosition(960.0f, 0.0f);
	downRight->SetPosition(960.0f, 512.0f);
	upLeft->SetPosition(0.0f, 0.0f);
	downLeft->SetPosition(0.0f, 512.0f);

	room->AddEntity(upRight);
	room->AddEntity(downRight);
	room->AddEntity(upLeft);
	room->AddEntity(downLeft);

	for (int x = 2; x < 30; ++x)
	{
		WallUp* wallUp = new WallUp();
		wallUp->SetPosition(x * 32.0f, 0.0f);
		room->AddEntity(wallUp);

		WallDown* wallDown = new WallDown();
		wallDown->SetPosition(x * 32.0f, 512.0f);
		room->AddEntity(wallDown);
	}

	for (int y = 2; y < 16; ++y)
	{
		WallLeft* wallLeft = new WallLeft();
		wallLeft->SetPosition(0.0f, y * 32.0f);
		room->AddEntity(wallLeft);

		WallRight* wallRight = new WallRight();
		wallRight->SetPosition(960.0f, y * 32.0f);
		room->AddEntity(wallRight);
	}

	for (int y = 2; y < 16; ++y)
	{
		for (int x = 2; x < 30; ++x)
		{
			FloorTile* tile = new FloorTile();
			tile->SetPosition(x * 32.0f, y * 32.0f);
			room->AddEntity(tile);
		}
	}
	room->AddEntity(player);
}
