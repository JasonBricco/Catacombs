
#include "Stdafx.h"
#include "Generator.h"
#include "Player.h"

void BasicGenerator::Build(Level* level)
{
	Room* room = level->GetOrCreateRoom(0, 0);

	Player* player = new Player();
	

	player->SetPosition(100.0f, 100.0f);

	level->SetCurrentRoom(room);

	for (int y = 0; y < 18; ++y)
	{
		for (int x = 0; x < 32; ++x)
		{
			FloorTile* tile = new FloorTile();
			tile->SetPosition(x * 32.0f, y * 32.0f);
			room->AddEntity(tile);
		}
	}
	room->AddEntity(player);
}
