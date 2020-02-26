
#include "Stdafx.h"
#include "Level.h"

Room* Level::GetOrCreateRoom(int x, int y)
{
	Vector2i pos(x, y);
	auto it = rooms.find(pos);

	if (it == rooms.end())
	{
		Room* room = new Room();
		room->SetPosition(x, y);
		rooms.insert(std::make_pair(pos, room));
		return room;
	}

	return it->second;
}

void Level::Update(float elapsed)
{
	assert(currentRoom != nullptr);
	currentRoom->Update(this, elapsed);
}

void Level::Draw(sf::RenderWindow& window)
{
	assert(currentRoom != nullptr);
	currentRoom->Draw(window);
}
