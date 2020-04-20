#pragma once

#include "Entity.h"
#include "Utils.h"
#include "Inventory.h"
#include "HealthBar.h"

class Player : public DynamicEntity
{
	void ChangeRooms(Level* level, int offX, int offY);

	// Attack frequency.
	float atkFreq = 0.25f, atkTimeLeft = 0.0f;

	int keys;
	Inventory* inventory;
	HealthBar* healthBar;

	Text scoreText;
	Assets* assets = Assets::Instance();
	Font& font = assets->GetFont("Assets/Arial.ttf");

public:
	Player()
	{
		id = EntityID::Player;

		LoadTexture(sprites[LEFT], "Assets/hero-idle-side-left.png");
		LoadTexture(sprites[RIGHT], "Assets/hero-idle-side-right.png");
		LoadTexture(sprites[DOWN], "Assets/hero-idle-front.png");
		LoadTexture(sprites[UP], "Assets/hero-idle-back.png");

		// Create move animation clips.
		Sprite moveSprites[4];
		LoadTexture(moveSprites[LEFT], "Assets/hero-walk-left.png");
		LoadTexture(moveSprites[RIGHT], "Assets/hero-walk-right.png");
		LoadTexture(moveSprites[UP], "Assets/hero-walk-back.png");
		LoadTexture(moveSprites[DOWN], "Assets/hero-walk-front.png");
		
		CreateClip(move, LEFT, moveSprites[LEFT], Vector2i(64, 64), 6, 8.0f, false, true);
		CreateClip(move, RIGHT, moveSprites[RIGHT], Vector2i(64, 64), 6, 8.0f, false);
		CreateClip(move, DOWN, moveSprites[DOWN], Vector2i(64, 64), 6, 8.0f, false);
		CreateClip(move, UP, moveSprites[UP], Vector2i(64, 64), 6, 8.0f, false);

		// Create attack animation clips.
		Sprite atkSprites[4];
		LoadTexture(atkSprites[LEFT], "Assets/hero-attack-left.png");
		LoadTexture(atkSprites[RIGHT], "Assets/hero-attack-right.png");
		LoadTexture(atkSprites[UP], "Assets/hero-attack-back.png");
		LoadTexture(atkSprites[DOWN], "Assets/hero-attack-front.png");

		CreateClip(attack, LEFT, atkSprites[LEFT], Vector2i(64, 64), 3, 30.0f, true, true);
		CreateClip(attack, RIGHT, atkSprites[RIGHT], Vector2i(64, 64), 3, 30.0f, true);
		CreateClip(attack, DOWN, atkSprites[DOWN], Vector2i(64, 64), 3, 30.0f, true);
		CreateClip(attack, UP, atkSprites[UP], Vector2i(64, 64), 3, 30.0f, true);

		facing = DOWN;
		sprite = sprites[facing];
		layer = 50;

		speed = 100.0f;
		size = Vector2f(0.95f, 0.5f);
		offset = Vector2f(0.525f, 1.5f);

		keys = 0;

		collideType = CollideType::Overlap;
		inventory = new Inventory();

		healthBar = new HealthBar();

		scoreText = Text("Score:", font, 15);
		scoreText.setFillColor(sf::Color::Yellow);
	}

	inline Inventory* GetInventory()
	{
		return inventory;
	}

	void Kill(Level* level) override;
	void HandleOverlaps(Level* level) override;
	void Update(Level* level, float elapsed) override;
	void Draw(Renderer& rend) override;
};
