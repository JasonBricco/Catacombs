
#include "Stdafx.h"
#include "Room.h"

void Room::Update(Level* level, float elapsed)
{
	for (Entity* entity : entities)
		entity->Update(level, elapsed);
}

void Room::Draw(Renderer& rend)
{
	for (Entity* entity : entities)
	{
		if (entity->Visible())
			entity->Draw(rend);
	}
}
