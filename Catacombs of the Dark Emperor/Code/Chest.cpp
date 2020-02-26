#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"

void Chest::spawn(Player* player)
{
	this->player = player;

	int x = randomInRange(2, Room::Width - 3);
	int y = randomInRange(2, Room::Height - 3);
	this->SetPosition(x, y);
}

void Chest::Update(Level*, float)
{
	Vector2f chestP = Vector2f(position.x + 0.5f, position.y + 0.5f);

	Vector2f playerP = player->GetPosition();
	playerP.x += 1.0f;
	playerP.y += 1.5f;

	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		float dist = Distance(playerP, chestP);

		if (dist < 1.5f)
		{
			open();
		}
	}
}

void Chest::open()
{
	sprite = sprites[UP];
}