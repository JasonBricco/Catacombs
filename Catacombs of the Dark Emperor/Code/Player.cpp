
#include "Stdafx.h"
#include "Player.h"
#include "Assets.h"
#include "Utils.h"

void Player::Update(Level* level, float elapsed)
{
	Vector2f accel = Vector2(0.0f, 0.0f);


	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		sprite = sprites[LEFT];
		accel.x -= 1.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		sprite = sprites[RIGHT];
		accel.x += 1.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		sprite = sprites[DOWN];
		accel.y += 1.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		sprite = sprites[UP];
		accel.y -= 1.0f;
	}

	

	// Ensure the movement vector is at most length 1,
	// to prevent moving faster on diagonals.
	if (accel != Vector2f(0.0f, 0.0f))
		accel = Normalize(accel);

	Move(level, accel, elapsed);
}
