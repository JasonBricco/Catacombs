#pragma once
#include "Stdafx.h"
#include "Entity.h"
#include "Utils.h"
#include "Items.h"

class Inventory : public Entity
{
	bool InventoryOpen = false;
	Sprite invent;
	std::vector<int> inventoryItem;
	std::vector<int> itemCount;
	Sprite playerimage;
	Items* item = new Items();
	const float cellSizeX = 135.0f;
	const float cellSizeY = 100.0f;
	const int cellCount = 3;
	float gridStartX = 355.0f;
	float gridStartY = 220.0f;

public:

	Inventory()
	{
		LoadTexture(playerimage, "Assets/hero-idle-front.png" );
		playerimage.setPosition(sf::Vector2f(477, 105));
		LoadTexture(invent, "Assets/ChestInterface.png");
		invent.setPosition(Vector2f(260, 100));
		this->SetPosition(1000, 1000);
	}

	void Update(Level* level, float elapsed) override;

	void Draw(Renderer& rend) override;

	void Insert(int ItemNumber);

};