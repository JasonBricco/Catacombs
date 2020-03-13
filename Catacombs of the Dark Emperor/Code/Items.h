#pragma once
#include "Entity.h"
#include "Utils.h"

class Items : public Entity
{
public:
	Sprite Item[3];
	Items()
	{
		LoadTexture(Item[0], "Assets/Shield.png");
		LoadTexture(Item[1], "Assets/ArrowRight.png");
		LoadTexture(Item[2], "Assets/FireballRight.png");
	}
};