
#include "Stdafx.h"
#include "Room.h"

void Room::Update(float elapsed)
{
	for (Entity* entity : entities)
		entity->Update(elapsed);
}

void Room::Draw(sf::RenderWindow& window)
{
	for (Entity* entity : entities)
		entity->Draw(window);
}
