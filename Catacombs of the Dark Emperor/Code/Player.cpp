#include "Stdafx.h"
#include "Player.h"
#include "Assets.h"
#include "Utils.h"
#include "Room.h"
#include "Level.h"
#include "HealthBar.h"
#include "Projectiles.h"

void Player::Update(Level* level, float elapsed)
{
	if (topscore < score)
	{
		topscore = score;
	}

	health = std::min(health + inventory->GetIncreasedHealth(), maxHealth);
	inventory->SetIncreasedHealth(0);

	Entity::Update(level, elapsed);
	Vector2f accel = Vector2(0.0f, 0.0f);

	playerPosition = GetCenter();

	int attackI = 4 + inventory->GetIncreasedAttack();

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		facing = LEFT;
		accel.x -= 1.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		facing = RIGHT;
		accel.x += 1.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		facing = DOWN;
		accel.y += 1.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		facing = UP;
		accel.y -= 1.0f;
	}

	// Choose whether we should use animation or 
	// idle frames based on user input.
	if (accel != Vector2f(0.0f, 0.0f))
	{
		// Choose a move animation.
		switch (facing)
		{
		case LEFT: SetAnimation(& move[LEFT]); break;
		case RIGHT: SetAnimation(& move[RIGHT]); break;
		case DOWN: SetAnimation(& move[DOWN]); break;
		case UP: SetAnimation(&move[UP]); break;
		}
	}
	else
	{
		// Choose an idle sprite.
		switch (facing)
		{
		case LEFT: sprite = sprites[LEFT]; break;
		case RIGHT: sprite = sprites[RIGHT]; break;
		case DOWN: sprite = sprites[DOWN]; break;
		case UP: sprite = sprites[UP]; break;
		}

		SetAnimation(nullptr);
	}

	atkTimeLeft -= elapsed;

	//implements player attack
	if (atkTimeLeft <= 0.0f && Keyboard::isKeyPressed(Keyboard::E))
	{
		Room* room = level->GetCurrentRoom();

		if (!inventory->IsBowEquipped())
		{
			sounds->playSwordSound();

			for (Entity* e : room->GetEntities())
			{
				if (Distance(e->GetPosition(), GetPosition()) < 3.0f)
				{
					switch (e->ID())
					{
					case EntityID::Enemy:
						Vector2 force = Normalize(e->GetPosition() - GetPosition()) * 30.0f;
						e->Damage(level, attackI, force);
						score++;
						inventory->DecreaseWeaponhealth();
						break;
					}
				}
			}

			SetAnimation(&attack[facing]);
			atkTimeLeft = atkFreq;
		}
		else
		{
			sounds->playBowSound();

			Vector2f dir = (Vector2f)directions[facing];
			dir.y = -dir.y;
		
			Arrow* arrow = room->AddEntity<Arrow>(0.0f, 0.f, facing, 5.0f);

			Vector2f next = BoundingBox().center + dir;

			if (facing == LEFT || facing == RIGHT)
				next.y -= 0.3f;

			arrow->SetCentered(next.x, next.y);

			SetAnimation(&bow[facing]);
			atkTimeLeft = wpnAtkFreq;
		}
	}

	// Ensure the movement vector is at most length 1,
	// to prevent moving faster on diagonals.
	if (accel != Vector2f(0.0f, 0.0f))
		accel = Normalize(accel);

	if (Keyboard::isKeyPressed(Keyboard::LShift))
		speed = 200.0f;
	else speed = 100.0f;

	Move(level, accel, elapsed);

	inventory->Update(level, elapsed);

	ComputeAnimation(elapsed);
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
			playerPosition = GetCenter();
			break;

		case EntityID::DoorDown:
			ChangeRooms(level, 0, -1);
			position.y = 1.0f;
			playerPosition = GetCenter();
			break;

		case EntityID::DoorLeft:
			ChangeRooms(level, -1, 0);
			position.x = Room::Width - 3.65f;
			playerPosition = GetCenter();
			break;

		case EntityID::DoorRight:
			ChangeRooms(level, 1, 0);
			position.x = 1.5f;
			playerPosition = GetCenter();
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
	
	getGameState().gameOver = true;

	level->Restart(3.0f);
}

void Player::Draw(Renderer& rend)
{
	Entity::Draw(rend);

	inventory->Draw(rend);
	healthBar->UpdateHearts(health);

	for (int i = 0; i < 8; i++) 
	{
		Heart* heart = healthBar->hearts[i];
		heart->SetPosition((float)(.55 * i), 18.0);
		heart->Draw(rend);
	}

	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setPosition((float)(400.0), 575);
	rend.Draw(&scoreText, 110);

	floorNumberText.setString("Floor B" + std::to_string(getGameState().floor));
	floorNumberText.setPosition((float)(955.0), 575);
	rend.Draw(&floorNumberText, 110);

	topScoreText.setString("Top Score: " + std::to_string(topscore));
	topScoreText.setPosition((float)(500.0), 575);
	rend.Draw(&topScoreText, 110);
}
