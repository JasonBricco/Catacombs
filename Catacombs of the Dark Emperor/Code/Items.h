#pragma once
#include "Entity.h"
#include "Utils.h"

class Items : public Entity
{
public:

	std::map<int, Sprite> Item;
	int ItemCount[totalItemsInInventory];

	Items()
	{
		for (int i = 0 ; i < totalItemsInInventory; i++)
		{
			ItemCount[i] = 0;
		}
		LoadTexture(Item[0], "Assets/Shield.png");
		LoadTexture(Item[1], "Assets/ArrowRight.png");
		LoadTexture(Item[2], "Assets/FireballRight.png");
		LoadTexture(Item[3], "Assets/BluePotion.png");
		LoadTexture(Item[4], "Assets/RedPotion.png");
		LoadTexture(Item[5], "Assets/GreenPotion.png");
		LoadTexture(Item[6], "Assets/OrangePotion.png");
		LoadTexture(Item[7], "Assets/axe.png");
		LoadTexture(Item[8], "Assets/sword.png");
	}
};