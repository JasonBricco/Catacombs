#include "Stdafx.h"
#include "Player.h"
#include "Assets.h"
#include "Utils.h"
#include "Room.h"
#include "Level.h"

void Player::Update(Level* level, float elapsed)
{
	Entity::Update(level, elapsed);
	Vector2f accel = Vector2(0.0f, 0.0f);

	playerPosition = this->GetPosition();

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

	inventory->Update(level, elapsed);
}

void Player::ChangeRooms(Level* level, int offX, int offY)
{
	Room* current = level->GetCurrentRoom();

	Vector2i nextP = current->GetPosition();
	nextP.x += offX;
	nextP.y += offY;

	Room* next = level->GetOrCreateRoom(nextP.x, nextP.y);
	level->SetCurrentRoom(next);

	current->RemoveEntity(this);
	next->AddEntity(this);
}

void Player::HandleOverlaps(Level* level)
{
	for (std::pair<Entity*, AABB> pair : overlaps)
	{
		Entity* e = pair.first;

		switch (e->ID())
		{
		case EntityID::DoorUp:
			ChangeRooms(level, 0, 1);
			position.y = Room::Height - 4.15f;
			break;

		case EntityID::DoorDown:
			ChangeRooms(level, 0, -1);
			position.y = 1.0f;
			break;

		case EntityID::DoorLeft:
			ChangeRooms(level, -1, 0);
			position.x = Room::Width - 3.65f;
			break;

		case EntityID::DoorRight:
			ChangeRooms(level, 1, 0);
			position.x = 1.5f;
			break;

		case EntityID::DoorStairsUp:
			getGameState().newLevel = true;
			getGameState().newLevelPrevDir = UP;
			break;

		case EntityID::DoorStairsDown:
			getGameState().newLevel = true;
			getGameState().newLevelPrevDir = DOWN;
			break;
		}
	}
}

void Player::Kill(Level* level)
{
	Entity::Kill(level);
	level->Restart(3.0f);
}

void Player::Draw(Renderer& rend)
{
	Entity::Draw(rend);

	inventory->Draw(rend);

	// TODO: Put healthbar drawing here.
	//rend.Draw(health_bar_sprite, layer_here);
	// or: for (int i = 0; i < heart_count; ++i) rend.draw(heart, layer);
	// You'll also need to call sprite.setPosition(x, y) to position them
	// properly before calling rend.draw().
}
