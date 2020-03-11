
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
}

void Level::Draw(Renderer& rend)
{
	assert(currentRoom != nullptr);
	currentRoom->Draw(rend);
}
