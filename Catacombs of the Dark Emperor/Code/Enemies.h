#pragma once

#include "Entity.h"
#include "Utils.h"
#include "Pathfinding.h"

class Slime : public DynamicEntity
{
	Path path;
	float recompute = 0.0f;
	bool needsUpdate = true;

	Vector2f nextP, lastPlayerP;
	bool hasNext = false;
	bool following = false;

	AnimationClip clip;

public:
	Slime(int x, int y)
	{
		id = EntityID::Enemy;
		layer = 45;
		
		Sprite s;
		LoadTexture(s, "Assets/Slime.png");

		CreateClip(&clip, 0, s, Vector2i(30, 28), 4, 4.0f, false, false);
		SetAnimation(&clip);

		collideType = CollideType::Overlap;
		sprite = sprites[DOWN];
		this->SetPosition(x,y);

		size = Vector2f(0.9f, 0.9f);
	}

	void HandleOverlaps(Level* level) override;
	void Update(Level* level, float elapsed) override;
};

class FireSkull : public DynamicEntity
{
	Path path;
	float recompute = 0.0f;
	bool needsUpdate = true;

	Vector2f nextP, lastPlayerP;
	bool hasNext = false;
	bool following = false;

	float fireTime = 0.0f;
	AnimationClip clip;

public:
	FireSkull(int x, int y)
	{
		id = EntityID::Enemy;
		layer = 45;

		Sprite s;
		LoadTexture(s, "Assets/Skull.png");

		CreateClip(&clip, 0, s, Vector2i(32, 54), 4, 4.0f, false, false);
		SetAnimation(&clip);

		collideType = CollideType::Overlap;
		sprite = sprites[DOWN];
		this->SetPosition(x, y);

		size = Vector2f(0.9f, 0.9f);
		offset = Vector2f(0.0f, 0.84f);
	}

	void HandleOverlaps(Level* level) override;
	void Update(Level* level, float elapsed) override;
};