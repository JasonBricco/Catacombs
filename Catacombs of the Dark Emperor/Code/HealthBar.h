#pragma once

#include "Entity.h"
#include "Utils.h"

class Heart : public DynamicEntity
{
public:
	Heart()
	{
		LoadTexture(sprites[0], "Assets/HeartFull.png");
		LoadTexture(sprites[1], "Assets/HeartHalf.png");
		LoadTexture(sprites[2], "Assets/HeartEmpty.png");
		LoadTexture(sprites[3], "Assets/HeartEmpty.png");

		sprite = sprites[0];

	};
};

class HealthBar
{

public:
	Heart* hearts[8];

	void UpdateHearts(int health);

	HealthBar(){
	
		for (int i = 0; i < 8; i++) {
			hearts[i] = new Heart();
		}
	}
	
	
};





