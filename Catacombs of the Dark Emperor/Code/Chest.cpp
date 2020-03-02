#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"
#include "Globals.h"

// giving type an int
// 1 is for red chest, 2 is for blue chest
void Chest::spawn(Player* playerPtr, int type)
{
	player = playerPtr;
	if (type == 1)
	{
		LoadTexture(sprites[DOWN], "Assets/redchestclosed.png");
		LoadTexture(sprites[UP], "Assets/redchestopen.png");
		sprite = sprites[DOWN];
	}

	else if (type == 2)
	{
		LoadTexture(sprites[DOWN], "Assets/bluechestclosed.png");
		LoadTexture(sprites[UP], "Assets/bluechestopen.png");
		sprite = sprites[DOWN];
	}
	int x = randomInRange(3, Room::Width - 4);
	int y = randomInRange(3, Room::Height - 4);
	this->SetPosition(x, y);
}

void Chest::Update(Level* level, float elapsed)
{
	Vector2f chestP = Vector2f(position.x + 0.5f, position.y + 0.5f);

	Vector2f playerP = player->GetPosition();
	playerP.x += 1.0f;
	playerP.y += 1.5f;

	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		dist = Distance(playerP, chestP);

		if (dist < 1.5f && IsChestOpen == false)
		{
			open();
		}
	}
}

void Chest::open()
{
	IsChestOpen = true;
	sprite = sprites[UP];
}

void Chest::Draw(RenderWindow& window)
{
	Vector2f drawP = position * PIXELS_PER_UNIT;

	sprite.setPosition(drawP);
	window.draw(sprite);
	if (Keyboard::isKeyPressed(Keyboard::E) && (dist < 1.5f))
	{
		IsChestContentOpen = true;
	}
	if (IsChestContentOpen == true)
	{
		window.draw(ChestContents);
		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			IsChestContentOpen = false;
		}
	}
}


