#include "Inventory.h"
#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"
#include "Globals.h"
#include "Renderer.h"

void Inventory::Draw(Renderer& rend)
{
	Vector2f drawP = position * PIXELS_PER_UNIT;

	sprite.setPosition(drawP);
	rend.Draw(sprite, 5);

	if (InventoryOpen == true)
	{
		rend.Draw(invent, 105);
		for (Sprite i : inventory)
		{
			rend.Draw(i, 110);
		}

		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			InventoryOpen = false;
			setGameState(false);
		}
		rend.Draw(playerimage, 110);
	}
}

void Inventory::Update(Level*, float)
{
	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		InventoryOpen = true;
		setGameState(true);
	}
}

void Inventory::Insert(Sprite sprite)
{
	inventory.push_back(sprite);
}