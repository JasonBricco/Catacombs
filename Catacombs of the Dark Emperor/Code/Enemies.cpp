#include "Stdafx.h"
#include "Enemies.h"
#include "Utils.h"

void Wolf::Update(Level* level, float elapsed)
{
	Entity::Update(level, elapsed);

	Vector2f accel = Vector2(0.0f, 0.0f);
	speed = 60.0f;

	Vector2f wolfP = GetCenter();

	if (!following)
	{
		float distance = Distance(playerPosition, wolfP);

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
				FindPath(level, TilePos(wolfP), TilePos(playerPosition), &path);
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
				Vector2 diff = nextP - wolfP;

				if (abs(diff.x) <= 0.5f && abs(diff.y) <= 0.5f)
					hasNext = false;
				
				accel = Normalize(diff);
				SetFacing(accel);
			}
		}
	}

	Move(level, accel, elapsed);
}

void Wolf::HandleOverlaps(Level* level)
{
	for (std::pair<Entity*, AABB> pair : overlaps)
	{
		Entity* e = pair.first;

		switch (e->ID())
		{
		case EntityID::Player:
			Vector2 force = Normalize(e->GetCenter() - GetCenter()) * 30.0f;
			e->Damage(level, 4, force);
			break;
		}
	}
}