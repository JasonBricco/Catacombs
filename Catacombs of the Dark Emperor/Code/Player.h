#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player() : Entity("Assets/hero-idle-front.png") 
	{
		speed = 100.0f;
		size = Vector2f(1.0f, 0.5f);
		offset = Vector2f(0.5f, 1.5f);
	}

	void Update(Level* level, float elapsed) override;
};
