#include "Stdafx.h"
#include "Projectiles.h"

void Arrow::HandleOverlaps(Level* level)
{
	for (std::pair<Entity*, AABB> pair : overlaps)
	{
		Entity* e = pair.first;

		switch (e->ID())
		{
		case EntityID::Enemy:
			Vector2 force = Normalize(e->GetCenter() - GetCenter()) * 30.0f;
			e->Damage(level, 4, force);
			Kill(level);
			break;
		}
	}
}

void Arrow::HandleCollide(Level* level)
{
	Kill(level);
}

void Arrow::Update(Level* level, float elapsed)
{
	time -= elapsed;

	if (time <= 0.0f)
		Kill(level);
	else
	{
		Vector2f accel = dir;
		speed = 200.0f;
		Move(level, accel, elapsed);
	}
}

void Fireball::HandleOverlaps(Level* level)
{
	for (std::pair<Entity*, AABB> pair : overlaps)
	{
		Entity* e = pair.first;

		switch (e->ID())
		{
		case EntityID::Player:
			if (*playershield)
				*playershield = false;
			else
			{
				Vector2 force = Normalize(e->GetCenter() - GetCenter()) * 30.0f;
				e->Damage(level, 4, force);
				Kill(level);
			}

			break;
		}
	}
}

void Fireball::HandleCollide(Level* level)
{
	Kill(level);
}

void Fireball::Update(Level* level, float elapsed)
{
	time -= elapsed;

	if (time <= 0.0f)
		Kill(level);
	else
	{
		Vector2f accel = dir;
		speed = 100.0f;
		Move(level, accel, elapsed);
		ComputeAnimation(elapsed);
	}
}

void Fireball::Draw(Renderer& rend)
{
	sprite.setOrigin(9.0f, 20.0f);
	sprite.setRotation(rotate);
	DynamicEntity::Draw(rend);
}
