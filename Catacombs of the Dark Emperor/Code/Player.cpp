
#include "Stdafx.h"
#include "Player.h"
#include "Assets.h"
#include "Utils.h"

void Player::Update(Level* level, float elapsed)
{
	Vector2f accel = Vector2(0.0f, 0.0f);

	if (Keyboard::isKeyPressed(Keyboard::W))
		accel.y -= 1.0f;

	if (Keyboard::isKeyPressed(Keyboard::A))
		accel.x -= 1.0f;

	if (Keyboard::isKeyPressed(Keyboard::S))
		accel.y += 1.0f;

	if (Keyboard::isKeyPressed(Keyboard::D))
		accel.x += 1.0f;

	// Ensure the movement vector is at most length 1,
	// to prevent moving faster on diagonals.
	if (accel != Vector2f(0.0f, 0.0f))
		accel = Normalize(accel);

	Move(level, accel, elapsed);
}
