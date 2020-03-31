#include "Stdafx.h"
#include "Enemies.h"

void Wolf::Update(Level* level, float elapsed)
{
	Entity::Update(level, elapsed);

	Vector2f accel = Vector2(0.0f, 0.0f);
	speed = 50.0f;

	Vector2f playerP = playerPosition;
	Vector2f wolfP = this->GetPosition();

	float XDist = playerP.x - wolfP.x;
	float YDist = playerP.y - wolfP.y;

	float distance = Distance(playerP, wolfP);
	if (distance < 10.0f) {
		if (XDist > 0) {
			accel.x += 1.0f;
		}
		else if (XDist < -1.0f) {
			accel.x -= 1.0f;
		}
		if (YDist < -1.0f) {
			accel.y -= 1.0f;
		}
		else if (YDist > 0) {
			accel.y += 1.0f;
		}
	}

	//gives directional sprites to wolf 
	if (accel.y < 0.0f) {
		sprite = sprites[UP];
	}
	else if (accel.y > 0.0f) {
		sprite = sprites[DOWN];
	}
	else if (accel.x < 0.0f) {
		sprite = sprites[LEFT];
	}
	else if (accel.x > 0.0f) {
		sprite = sprites[RIGHT];
	}

	// Ensure the movement vector is at most length 1,
	// to prevent moving faster on diagonals.
	if (accel != Vector2f(0.0f, 0.0f))
		accel = Normalize(accel);

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
			Vector2 force = Normalize(e->GetPosition() - GetPosition()) * 30.0f;
			e->Damage(level, 4, force);
			break;
		}
	}
}