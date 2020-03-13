#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"
#include "Chest.h"
#include "Room.h"
#include "Globals.h"
#include "Renderer.h"

// giving type an int
// 1 is for red chest, 2 is for blue chest
void Chest::spawn(Player* playerPtr, int type, int x, int y)
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
	rend.Draw(sprite, 5);

	if (Keyboard::isKeyPressed(Keyboard::E) && (dist < 1.5f))
	{
		IsChestContentOpen = true;
		setGameState(true);
	}
	if (IsChestContentOpen == true)
	{
		ChestImage.setPosition(sf::Vector2f(492,125));
		rend.Draw(ChestContents, 100);
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			IsChestContentOpen = false;
			setGameState(false);
		}
		if(itemTaken[0] == false)
			rend.Draw(item->Item[0], 110);
		if (itemTaken[1] == false)
			rend.Draw(item->Item[1], 110);
		if (itemTaken[2] == false)
			rend.Draw(item->Item[2], 110);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f mouseP = Vector2f(Mouse::getPosition());
			mouseP.x -= 450.0f;
			mouseP.y -= 300.0f;
			Vector2f item1P = item->Item[0].getPosition();
			item1P.x += 1.0f;
			item1P.y += 1.5f;
			float dist1 = Distance(mouseP, item1P);
			if (dist1 < 80.0f) 
			{
				itemTaken[0] = true;
			}
			Vector2f item2P = item->Item[1].getPosition();
			item2P.x += 1.0f;
			item2P.y += 1.5f;
			float dist2 = Distance(mouseP, item2P);
			if (dist2 < 80.0f)
			{
				itemTaken[1] = true;
			}
			Vector2f item3P = item->Item[2].getPosition();
			item3P.x += 1.0f;
			item3P.y += 1.5f;
			float dist3 = Distance(mouseP, item3P);
			if (dist3 < 80.0f)
			{
				itemTaken[2] = true;
			}
		}
		rend.Draw(ChestImage, 105);
	}
}


