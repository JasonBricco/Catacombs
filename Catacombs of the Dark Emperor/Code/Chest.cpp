#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"
#include "Player.h"

void Chest::spawn()
{
	int x = randomInRange(2, Room::Width - 3);
	int y = randomInRange(2, Room::Height - 3);
	this->SetPosition(x, y);
}

void Chest::Update(Level*, float)
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		open();
	}
}

void Chest::open()
{
	sprite = sprites[UP];
}