#pragma once

#include "Entity.h"

class Player : public Entity
{
	void move(int x);

	float changeX = 100.0f;
	float changeY = 100.0f;
	float speed = 3.0f;

public:
	Player() : Entity("Assets/hero-idle-front.png") {}

	void Update(float elapsed) override;
};
