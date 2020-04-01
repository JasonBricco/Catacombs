
#include "Stdafx.h"
#include "Level.h"

Room* Level::GetOrCreateRoom(int x, int y)
{
	Vector2i p(x, y);
	auto it = rooms.find(p);

	if (it == rooms.end())
	{
		Room* room = new Room();
		room->SetPosition(x, y);
		rooms.insert(std::make_pair(p, room));
		return room;
	}

	return it->second;
}

Room* Level::GetRoom(Vector2i p)
{
	auto it = rooms.find(p);
	assert(it != rooms.end());
	return it->second;
}

void Level::Update(float elapsed)
{
	assert(currentRoom != nullptr);
	currentRoom->Update(this, elapsed);

	// Destroy entities after updating is done,
	// so we don't destroy mid-iteration.
	for (Entity* entity : pendingDestroy)
	{
		currentRoom->RemoveEntity(entity);
		delete entity;
	}

	pendingDestroy.clear();

	if (restartPending)
	{
		restartTime -= elapsed;

		if (restartTime <= 0.0f)
		{
			getGameState().restart = true;
			restartPending = false;
		}
	}
}

void Level::Draw(Renderer& rend)
{
	assert(currentRoom != nullptr);
	currentRoom->Draw(rend);
}

void Level::Destroy()
{
	for (auto pair : rooms)
	{
		auto entities = pair.second->GetEntities();

		for (Entity* entity : pair.second->GetEntities())
		{
			// Don't delete the player - it should always persist.
			// Remove it instead. We still reference it in the generator,
			// which will place it in the new level.
			if (entity->ID() == EntityID::Player)
				pair.second->RemoveEntity(entity);
			else delete entity;
		}
	}
}
