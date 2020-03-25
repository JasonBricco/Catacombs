#pragma once

#include "Entity.h"
#include "Utils.h"

class FloorTile : public Entity
{
public:
	FloorTile() : Entity("Assets/BlueFloorTile.png")
	{
		collideType = CollideType::Passable;
	}
};

class WallUp : public Entity
{
public:
	WallUp() : Entity("Assets/DungeonWall0.png") {}
};

class WallDown : public Entity
{
public:
	WallDown() : Entity("Assets/DungeonWall2.png") {}
};

class WallLeft : public Entity
{
public:
	WallLeft() : Entity("Assets/DungeonWall3.png") {}
};

class WallRight : public Entity
{
public:
	WallRight() : Entity("Assets/DungeonWall1.png") {}
};

class WallCorner : public Entity
{
public:
	WallCorner(int variant)
	{
		switch (variant)
		{
		case UP_LEFT:
			LoadTexture(sprite, "Assets/DungeonCorner0.png"); break;

		case UP_RIGHT:
			LoadTexture(sprite, "Assets/DungeonCorner1.png"); break;

		case DOWN_RIGHT:
			LoadTexture(sprite, "Assets/DungeonCorner2.png"); break;

		case DOWN_LEFT: 
			LoadTexture(sprite, "Assets/DungeonCorner3.png"); break;
		
		case UP_LEFT + 4:
			LoadTexture(sprite, "Assets/Corner1.png"); break;

		case UP_RIGHT + 4:
			LoadTexture(sprite, "Assets/Corner2.png"); break;

		case DOWN_LEFT + 4:
			LoadTexture(sprite, "Assets/Corner3.png"); break;

		case DOWN_RIGHT + 4:
			LoadTexture(sprite, "Assets/Corner4.png"); break;
		}
	}
};

class DoorUp : public Entity
{
public: 
	DoorUp() : Entity("Assets/DungeonDoor0.png") 
	{
		collideType = CollideType::Overlap;
		id = EntityID::DoorUp;
	}
};

class DoorDown : public Entity
{
public:
	DoorDown() : Entity("Assets/DungeonDoor2.png")
	{
		collideType = CollideType::Overlap;
		id = EntityID::DoorDown;
	}
};

class DoorLeft : public Entity
{
public:
	DoorLeft() : Entity("Assets/DungeonDoor3.png")
	{
		collideType = CollideType::Overlap;
		id = EntityID::DoorLeft;
	}
};

class DoorRight : public Entity
{
public:
	DoorRight() : Entity("Assets/DungeonDoor1.png")
	{
		collideType = CollideType::Overlap;
		id = EntityID::DoorRight;
	}
};

class BarredDoor : public Entity
{
public:
	BarredDoor(int variant)
	{
		switch (variant)
		{
		case UP:
			LoadTexture(sprite, "Assets/BarredDoorUp.png"); break;

		case DOWN:
			LoadTexture(sprite, "Assets/BarredDoorDown.png"); break;
		}
	}
};

class DoorStairs : public Entity
{
public:
	DoorStairs(int variant)
	{
		switch (variant)
		{
		case UP:
			LoadTexture(sprite, "Assets/DungeonDoorStairsUp.png"); 
			id = EntityID::DoorStairsUp;
			break;

		case DOWN:
			LoadTexture(sprite, "Assets/DungeonDoorStairsDown.png"); 
			id = EntityID::DoorStairsDown;
			break;
		}

		collideType = CollideType::Overlap;
	}
};

class Barrier : public Entity
{
public:
	Barrier(float width, float height, float offsetX = 0.0f, float offsetY = 0.0f)
	{
		visible = false;
		size = Vector2f(width, height);
		offset = Vector2f(offsetX, offsetY);
	}
};

class PotTile : public Entity
{
public:
	PotTile() : Entity("Assets/Pot.png") 
	{
		layer = 5;
	}
};

class LampTile : public Entity
{

};

class PillarTile : public Entity
{

};

class RocksTile : public Entity
{
public:
	RocksTile()
	{
		if (randomUnit() < 0.35f)
			LoadTexture(sprite, "Assets/Rocks-2.png");
		else LoadTexture(sprite, "Assets/Rocks-1.png");

		layer = 5;
	}
};

class BlockTile : public Entity
{
public:
	BlockTile() : Entity("Assets/Block.png")
	{
		layer = 5;
	}
};
