#pragma once

#include "Entity.h"
#include "Utils.h"

class Wolf : public DynamicEntity
{
public:
	Wolf(int x, int y): DynamicEntity()
	{
		layer = 50;
		LoadTexture(sprites[LEFT], "Assets/monster_wolfC.png");
		LoadTexture(sprites[RIGHT], "Assets/monster_wolfB.png");
		LoadTexture(sprites[DOWN], "Assets/monster_wolfD.png");
		LoadTexture(sprites[UP], "Assets/monster_wolfA.png");
		collideType = CollideType::Overlap;
		sprite = sprites[DOWN];
		this->SetPosition(x,y);
	}

	void HandleOverlaps(Level* level) override;
	void Update(Level* level, float elapsed) override;
};
