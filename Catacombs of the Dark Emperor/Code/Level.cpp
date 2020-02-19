
#include "Stdafx.h"
#include "Level.h"

Room* Level::GetOrCreateRoom(int x, int y)
{
	sf::Vector2i pos(x, y);
	auto it = rooms.find(pos);

	if (it == rooms.end())
	{
		Room* room = new Room();
		rooms.insert(std::make_pair(pos, room));
		return room;
	}

	return it->second;
}

void Level::Update(float elapsed)
{
	assert(currentRoom != nullptr);
	currentRoom->Update(elapsed);
}

void Level::Draw(sf::RenderWindow& window)
{
	assert(currentRoom != nullptr);
	currentRoom->Draw(window);
}
