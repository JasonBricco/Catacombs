#pragma once
#include "Entity.h"
#include "Utils.h"

class Items : public Entity
{
public:

	std::map<int, Sprite> Item;
	int ItemCount[3];

	Items()
	{
		for (int i = 0 ; i < 3; i++)
		{
			ItemCount[i] = 0;
		}
		LoadTexture(Item[0], "Assets/Shield.png");
		LoadTexture(Item[1], "Assets/ArrowRight.png");
		LoadTexture(Item[2], "Assets/FireballRight.png");
	}
};