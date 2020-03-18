#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"
#include "Globals.h"
#include "Renderer.h"

// giving type an int
// 1 is for red chest, 2 is for blue chest
void Chest::spawn(Player* playerPtr, Inventory* inventory, int type, int x, int y)
{
	invent = inventory;
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
	ChestImage = sprites[DOWN];
	
	this->SetPosition(x, y);

}

void Chest::Update(Level*, float)
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

void Chest::Draw(Renderer& rend)
{
	Vector2f drawP = position * PIXELS_PER_UNIT;

	sprite.setPosition(drawP);
	rend.Draw(&sprite, 5);

	if (Keyboard::isKeyPressed(Keyboard::E) && (dist < 1.5f) && getGameState() == false)
	{
		IsChestContentOpen = true;
		setGameState(true);
	}
	if (IsChestContentOpen == true)
	{
		ChestImage.setPosition(sf::Vector2f(492,125));
		rend.Draw(&ChestContents, 100);
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			IsChestContentOpen = false;
			setGameState(false);
		}
		for (int i = 0; i < NumberOfItemsToAppear; i++)
		{
			if (itemTaken[i] == false)
				rend.Draw(&itemsInChest[i], 110);
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f mouseP = Vector2f(Mouse::getPosition());
			mouseP.x -= 450.0f;
			mouseP.y -= 300.0f;
			for (int i = 0; i < NumberOfItemsToAppear; i++)
			{
				Vector2f itemP = itemsInChest[i].getPosition();
				itemP.x += 1.0f;
				itemP.y += 1.5f;
				float dist1 = Distance(mouseP, itemP);
				if (dist1 < 80.0f)
				{
					itemTaken[i] = true;
					invent->Insert(ItemNumber[i]);
				}
			}
		}
		rend.Draw(&ChestImage, 105);
	}
}


