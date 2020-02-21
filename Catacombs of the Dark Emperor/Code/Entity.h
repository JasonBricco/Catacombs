#pragma once

class Entity
{
	sf::Sprite sprite;

protected:
	sf::Vector2f position;

public:
	Entity(std::string name);

	inline void SetPosition(float x, float y)
	{
		position = sf::Vector2f(x, y);
	}

	virtual void Update(float) {}
	void Draw(sf::RenderWindow& window);
};

class FloorTile : public Entity
{
public:
	FloorTile() : Entity("Assets/BlueFloorTile.png") {}
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