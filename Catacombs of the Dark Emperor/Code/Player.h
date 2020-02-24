#pragma once

#include "Entity.h"
#include "Utils.h"

class Player : public DynamicEntity
{
public:
	Player()
	{
		LoadTexture(sprites[LEFT], "Assets/hero-idle-side-left.png");
		LoadTexture(sprites[RIGHT], "Assets/hero-idle-side-right.png");
		LoadTexture(sprites[DOWN], "Assets/hero-idle-front.png");
		LoadTexture(sprites[UP], "Assets/hero-idle-back.png");

		sprite = sprites[DOWN];

		speed = 100.0f;
		size = Vector2f(1.0f, 0.5f);
		offset = Vector2f(0.5f, 1.5f);
	}

	void Update(Level* level, float elapsed) override;
};
