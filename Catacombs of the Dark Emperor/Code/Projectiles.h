#pragma once

#include "Entity.h"
#include "Utils.h"

class Arrow : public DynamicEntity
{
	Vector2f dir;
	float time;

public:
	Arrow(int dirIndex, float time) : dir(directions[dirIndex]), time(time)
	{
		switch (dirIndex)
		{
		case LEFT: LoadTexture(sprites[LEFT], "Assets/ArrowLeft.png"); break;
		case RIGHT: LoadTexture(sprites[RIGHT], "Assets/ArrowRight.png"); break;
		case UP: LoadTexture(sprites[UP], "Assets/ArrowUp.png"); break;
		case DOWN: LoadTexture(sprites[DOWN], "Assets/ArrowDown.png"); break;
		}
		
		sprite = sprites[dirIndex];
		dir.y = -dir.y;

		layer = 46;
		collideType = CollideType::Overlap;
	}

	void HandleOverlaps(Level* level) override;
	void HandleCollide(Level* level) override;
	void Update(Level* level, float elapsed) override;
};


class Fireball : public DynamicEntity
{
	Vector2f dir;
	float time, rotate;
	AnimationClip clip;

public:
	Fireball(Vector2f dir, float time) : dir(dir), time(time)
	{
		Sprite s;
		LoadTexture(s, "Assets/Fireball.png");

		CreateClip(&clip, 0, s, Vector2i(18, 40), 4, 5.0f, false, false);
		SetAnimation(&clip);

		layer = 46;
		collideType = CollideType::Overlap;

		size = Vector2f(1.0f, 1.0f);
		offset = Vector2f(-0.5f, -0.5f);

		rotate = AngleBetween(Vector2f(0.0f, 1.0f), dir);

		if (dir.x > 0.0f)
			rotate = PI2 - rotate;
	}

	void HandleOverlaps(Level* level) override;
	void HandleCollide(Level* level) override;
	void Update(Level* level, float elapsed) override;
	void Draw(Renderer& rend) override;
};
