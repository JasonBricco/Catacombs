#pragma once
#include "Stdafx.h"
#include "Entity.h"
#include "Utils.h"
#include "Items.h"
#include "Assets.h"

class Inventory : public Entity
{
	bool InventoryOpen = false;
	Sprite invent;
	std::vector<int> inventoryItem;
	Sprite playerimage;
	Items* item = new Items();
	const float cellSizeX = 135.0f;
	const float cellSizeY = 100.0f;
	const int cellCount = 3;
	float gridStartX = 355.0f;
	float gridStartY = 220.0f;
	Text tx[9];
	Assets* assets = Assets::Instance();
	Font& font = assets->GetFont("Assets/Arial.ttf");
	bool pressed = false;
	bool shieldEquipped = false;
	int increaseAttack = 0;
	int increaseHealth = 0;
	int weaponHealth = 0;
	bool bowEquipped = false;

public:

	Inventory()
	{
		LoadTexture(playerimage, "Assets/hero-idle-front.png" );
		playerimage.setPosition(sf::Vector2f(477, 105));
		LoadTexture(invent, "Assets/ChestInterface.png");
		invent.setPosition(Vector2f(260, 100));
		this->SetPosition(1000, 1000);
		for (int i = 0 ; i < 9; i++)
		{
			tx[i] = Text("",font,20) ;
			tx[i].setFillColor(sf::Color::Black);
			tx[i].setOutlineColor(Color(210, 125, 44));
			tx[i].setOutlineThickness(5);
		}
	}

	void Update(Level* level, float elapsed) override;

	void Draw(Renderer& rend) override;

	void Insert(int ItemNumber);

	bool IsShieldEquipped();
	
	inline bool IsBowEquipped()
	{
		return bowEquipped;
	}

	int GetIncreasedAttack();

	int GetIncreasedHealth();

	void SetShieldEquipped(bool statement);

	void SetIncreasedAttack(int attack);

	void SetIncreasedHealth(int health);

	void DecreaseWeaponhealth();

};