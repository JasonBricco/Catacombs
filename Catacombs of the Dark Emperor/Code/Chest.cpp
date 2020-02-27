#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"

void Chest::spawn(Player* playerPtr)
{
	player = playerPtr;

	int x = randomInRange(3, Room::Width - 4);
	int y = randomInRange(3, Room::Height - 4);
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