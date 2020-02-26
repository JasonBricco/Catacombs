#pragma once

#include "Entity.h"

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

class WallUpRight : public Entity
{
public:
	WallUpRight() : Entity("Assets/DungeonCorner1.png") {}
};

class WallDownRight : public Entity
{
public:
	WallDownRight() : Entity("Assets/DungeonCorner2.png") {}
};

class WallUpLeft : public Entity
{
public:
	WallUpLeft() : Entity("Assets/DungeonCorner0.png") {}
};

class WallDownLeft : public Entity
{
public:
	WallDownLeft() : Entity("Assets/DungeonCorner3.png") {}
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
