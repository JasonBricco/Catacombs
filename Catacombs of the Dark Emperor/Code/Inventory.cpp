#include "Inventory.h"
#include "Stdafx.h"
#include "Utils.h"
#include "Room.h"
#include "Globals.h"
#include "Renderer.h"
#include "Chest.h"

void Inventory::Draw(Renderer& rend)
{
	if (weaponHealth == 0)
	{
		increaseAttack = 0;
	}
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
			//int num = item->ItemCount[i];
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
			getGameState().paused = false;
			pressed = false;
		}
		rend.Draw(&playerimage, 110);



		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (!pressed)
			{
				pressed = true;
				Vector2f mouseP = rend.getWindow()->mapPixelToCoords(Mouse::getPosition(*rend.getWindow()));
				for (int i : inventoryItem)
				{
					Vector2f itemP = item->Item[i].getPosition();
					itemP.x += 1.0f;
					itemP.y += 1.5f;
					float dist1 = Distance(mouseP, itemP);
					if (dist1 < 60.0f)
					{
						if (item->ItemCount[i] > 0)
						{
							item->ItemCount[i]--;
							switch (i)
							{
							case 0:
								if (shieldEquipped)
									item->ItemCount[i]++;
								else
									shieldEquipped = true;
								break;
							case 1:
								bowEquipped = true;
								break;
							case 2:
								increaseHealth += 1;
								break;
							case 3:
								increaseHealth += 2;
								break;
							case 4:
								increaseHealth += 3;
								break;
							case 5:
								increaseHealth += 4;
								break;
							case 6:
								increaseAttack = 12;
								weaponHealth = 4;
								break;
							case 7:
								increaseAttack = 4;
								weaponHealth = 6;
								break;
							}
							break;
						}
					}
				}
			}
		} 
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			pressed = false;
		}
	}
}

void Inventory::Update(Level*, float)
{
	playershield = &shieldEquipped;
	if (Keyboard::isKeyPressed(Keyboard::I) && !getGameState().paused)
	{
		InventoryOpen = true;
		getGameState().paused = true;
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

bool Inventory::IsShieldEquipped()
{
	return shieldEquipped;
}

int Inventory::GetIncreasedAttack()
{
	return increaseAttack;
}

int Inventory::GetIncreasedHealth()
{
	return increaseHealth;
}

void Inventory::SetShieldEquipped(bool statement)
{
	shieldEquipped = statement;
}

void Inventory::SetIncreasedAttack(int attack)
{
	increaseAttack = attack;
}

void Inventory::SetIncreasedHealth(int hp)
{
	increaseHealth = hp;
}

void Inventory::DecreaseWeaponhealth()
{
	if (weaponHealth == 0)
	{
		return;
	}
	weaponHealth--;
}

