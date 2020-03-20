#include "Inventory.h"
#include "Stdafx.h"
#include "Utils.h"
#include "Room.h"
#include "Globals.h"
#include "Renderer.h"
#include "Chest.h"

void Inventory::Draw(Renderer& rend)
{
	Vector2f drawP = position * PIXELS_PER_UNIT;
	sprite.setPosition(drawP);
	rend.Draw(&sprite, 5);

	if (InventoryOpen == true)
	{
		Vector2i gridP = Vector2i(0, 0);
		rend.Draw(&invent, 105);
		for (int i : inventoryItem)
		{
			float x = gridStartX + gridP.x * cellSizeX;
			float y = gridStartY + gridP.y * cellSizeY;

			item->Item[i].setPosition(x, y);
			rend.Draw(&item->Item[i], 110);
			tx[i].setPosition(x + 32, y + 25);
			int num = item->ItemCount[i];
			tx[i].setString("x"+std::to_string(item->ItemCount[i]));
			rend.Draw(&tx[i], 115);
			++gridP.x;

			if (gridP.x == cellCount)
			{
				gridP.x = 0;
				++gridP.y;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			InventoryOpen = false;
			setGameState(false);
		}
		rend.Draw(&playerimage, 110);
	}
}

void Inventory::Update(Level*, float)
{
	if (Keyboard::isKeyPressed(Keyboard::I) && getGameState() == false)
	{
		InventoryOpen = true;
		setGameState(true);
	}
}

void Inventory::Insert(int ItemNumber)
{
	item->ItemCount[ItemNumber]++;
	for (int i : inventoryItem)
	{
		if (ItemNumber == i)
		{
			return;
		}
	}
	inventoryItem.push_back(ItemNumber);
}