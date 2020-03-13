#pragma once
#include "Stdafx.h"
#include "Entity.h"
#include "Utils.h"

class Inventory : public Entity
{
	bool InventoryOpen = false;
	Sprite invent;
	std::vector<Sprite> inventory;
	int posi[3][2] = { {350, 215}, {490, 215}, {630, 215} };
	Sprite playerimage;

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

	void Insert(Sprite sprite);

};