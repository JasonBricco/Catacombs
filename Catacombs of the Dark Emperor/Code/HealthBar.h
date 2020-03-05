#pragma once

#include "Entity.h"
#include "Utils.h"

class Heart : public DynamicEntity
{
public:
	Heart()
	{
		LoadTexture(sprites[0], "Assets/HeartFull");
		LoadTexture(sprites[1], "Assets/HeartHalf");
		LoadTexture(sprites[2], "Assets/HeartEmpty");
		LoadTexture(sprites[3], "Assets/HeartEmpty");

		sprite = sprites[0];

	};
};

class HealthBar
{
public:

	HealthBar()
	{
		Heart* heart1 = new Heart();
		Heart* heart2 = new Heart();
		Heart* heart3 = new Heart();
		Heart* heart4 = new Heart();
		Heart* heart5 = new Heart();
		Heart* heart6 = new Heart();
		Heart* heart7 = new Heart();
		Heart* heart8 = new Heart();
	}

};

void UpdateHearts(int health);

void BuildHealthBar(Level* level);


