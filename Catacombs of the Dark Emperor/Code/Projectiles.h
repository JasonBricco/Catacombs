#pragma once

#include "Entity.h"
#include "Utils.h"

class Arrow : public DynamicEntity
{
	Vector2f dir;
	float time;

public:
	Arrow(int dirIndex, float time) : dir(directions[dirIndex]), time(time)
	{
		switch (dirIndex)
		{
		case LEFT: LoadTexture(sprites[LEFT], "Assets/ArrowLeft.png"); break;
		case RIGHT: LoadTexture(sprites[RIGHT], "Assets/ArrowRight.png"); break;
		case UP: LoadTexture(sprites[UP], "Assets/ArrowUp.png"); break;
		case DOWN: LoadTexture(sprites[DOWN], "Assets/ArrowDown.png"); break;
		}
		
		sprite = sprites[dirIndex];
		dir.y = -dir.y;

		layer = 46;
		collideType = CollideType::Overlap;
	}

	void HandleOverlaps(Level* level) override;
	void HandleCollide(Level* level) override;
	void Update(Level* level, float elapsed) override;
};
