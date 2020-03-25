#pragma once

#include "Entity.h"

struct Wolf : public Entity
{
public:
	Wolf() : Entity("Assets/monster_wolfB.png") 
	{
		layer = 50;
		collideType = CollideType::Overlap;
	}
};
