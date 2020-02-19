
#include "Stdafx.h"
#include "Generator.h"
#include "Player.h"

void BasicGenerator::Build(Level* level)
{
	Room* room = level->GetOrCreateRoom(0, 0);

	Player* player = new Player();
	room->AddEntity(player);

	player->SetPosition(100.0f, 100.0f);

	level->SetCurrentRoom(room);
}
