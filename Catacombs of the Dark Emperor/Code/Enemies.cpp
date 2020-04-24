#include "Stdafx.h"
#include "Enemies.h"
#include "Utils.h"
#include "Projectiles.h"
#include "Level.h"

void Slime::Update(Level* level, float elapsed)
{
	Entity::Update(level, elapsed);

	Vector2f accel = Vector2(0.0f, 0.0f);
	speed = 50.0f;

	Vector2f slimeP = GetCenter();

	if (!following)
	{
		float distance = Distance(playerPosition, slimeP);

		if (distance < 10.0f)
			following = true;
	}

	if (following)
	{
		recompute -= elapsed;

		if (recompute <= 0.0f)
		{
			if (Distance(playerPosition, lastPlayerP) > 1.0f)
				needsUpdate = true;

			if (needsUpdate)
			{
				FindPath(level, TilePos(slimeP), TilePos(playerPosition), &path);
				recompute = 1.0f;
				lastPlayerP = playerPosition;
			}
		}

		if (path.Valid())
		{
			if (!hasNext)
			{
				nextP = path.Next();
				hasNext = true;
			}
			else
			{
				Vector2 diff = nextP - slimeP;

				if (abs(diff.x) <= 0.5f && abs(diff.y) <= 0.5f)
					hasNext = false;
				
				accel = Normalize(diff);
				SetFacing(accel);
			}
		}
	}

	Move(level, accel, elapsed);
	ComputeAnimation(elapsed);
}

void Slime::HandleOverlaps(Level* level)
{
	for (std::pair<Entity*, AABB> pair : overlaps)
	{
		Entity* e = pair.first;

		switch (e->ID())
		{
		case EntityID::Player:
			Vector2 force = Normalize(e->GetCenter() - GetCenter()) * 30.0f;
			if (*playershield)
			{
				e->Damage(level, 0, force);
				*playershield = false;
			}
			else
			{
				sounds->playDamageSound();
				e->Damage(level, 4, force);
			}
			break;
		}
	}
}

void FireSkull::Update(Level* level, float elapsed)
{
	Entity::Update(level, elapsed);

	Vector2f accel = Vector2(0.0f, 0.0f);
	speed = 50.0f;

	Vector2f skullP = GetCenter();

	float distance = Distance(playerPosition, skullP);
	recompute -= elapsed;

	if (distance >= 10.0f)
	{	
		if (recompute <= 0.0f)
		{
			if (Distance(playerPosition, lastPlayerP) > 1.0f)
				needsUpdate = true;

			if (needsUpdate)
			{
				FindPath(level, TilePos(skullP), TilePos(playerPosition), &path);
				recompute = 1.0f;
				lastPlayerP = playerPosition;
			}
		}

		if (path.Valid())
		{
			if (!hasNext)
			{
				nextP = path.Next();
				hasNext = true;
			}
			else
			{
				Vector2 diff = nextP - skullP;

				if (abs(diff.x) <= 0.5f && abs(diff.y) <= 0.5f)
					hasNext = false;

				accel = Normalize(diff);
				SetFacing(accel);
			}
		}
	}
	else
	{
		fireTime -= elapsed;

		if (fireTime <= 0.0f)
		{
			Vector2f dir = Normalize(playerPosition - position);
			Fireball* fire = level->GetCurrentRoom()->AddEntity<Fireball>(0.0f, 0.0f, dir, 5.0f);

			sounds->playFireball();

			Vector2f next = BoundingBox().center + dir;

			if (facing == LEFT || facing == RIGHT)
				next.y -= 0.3f;

			fire->SetCentered(next.x, next.y);
			fireTime = 1.0f;
		}
	}

	Move(level, accel, elapsed);
	ComputeAnimation(elapsed);
}

void FireSkull::HandleOverlaps(Level* level)
{
	for (std::pair<Entity*, AABB> pair : overlaps)
	{
		Entity* e = pair.first;

		switch (e->ID())
		{
		case EntityID::Player:
			Vector2 force = Normalize(e->GetCenter() - GetCenter()) * 30.0f;
			if (*playershield)
			{
				e->Damage(level, 0, force);
				*playershield = false;
			}
			else
			{
				sounds->playDamageSound();
				e->Damage(level, 4, force);
			}
			break;
		}
	}
}
