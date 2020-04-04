#pragma once

#include "Entity.h"
#include "Utils.h"
#include "Pathfinding.h"

class Wolf : public DynamicEntity
{
	Path path;
	float recompute = 0.0f;

	Vector2f nextP;
	bool hasNext = false;

	bool following = false;

public:
	Wolf(int x, int y): DynamicEntity()
	{
		id = EntityID::Wolf;
		layer = 45;
		LoadTexture(sprites[LEFT], "Assets/monster_wolfC.png");
		LoadTexture(sprites[RIGHT], "Assets/monster_wolfB.png");
		LoadTexture(sprites[DOWN], "Assets/monster_wolfD.png");
		LoadTexture(sprites[UP], "Assets/monster_wolfA.png");
		collideType = CollideType::Overlap;
		sprite = sprites[DOWN];
		this->SetPosition(x,y);

		size = Vector2f(0.9f, 0.9f);
		offset = Vector2f(0.5f, 0.5f);
	}

	void HandleOverlaps(Level* level) override;
	void Update(Level* level, float elapsed) override;
};
