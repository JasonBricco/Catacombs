#pragma once

#include "Collision.h"

class Level;

class Entity
{
	Sprite sprite;

	// Temporary storage to store bounding boxes we have to check for collision. 
	// It's static because only one entity will utilize it at a time.
	// This is more efficient for memory.
	static std::vector<AABB> collides;

protected:
	// Size is used for collision. It's the size in world units. A 32x32 pixel
	// entity would have a size here of 1x1. Offset is the relative position 
	// from the entity's pivot point for the collision box to be.
	Vector2f size, position;
	Vector2f velocity = {};
	Vector2f offset = {};

	// Tracks on which sides this entity collided during the 
	// last collision step.
	uint32_t colFlags = CF_NONE;

	// Whether this entity will be collided with.
	bool passable = false;

	float speed = 0.0f;

	// Moves the entity based on the set acceleration.
	void Move(Level* level, Vector2f accel, float elapsed);

public:
	// Name is the name of the texture to load for this entity.
	// By default, the pivot is the upper-left corner. 
	// Setting useBottomCenterPivot makes it the bottom center.
	Entity(std::string name);
	
	inline AABB BoundingBox()
	{
		return AABBFromCorner(position + offset, size);
	}

	inline void SetPosition(float x, float y)
	{
		position = sf::Vector2f(x, y);
	}

	inline void SetPosition(int x, int y)
	{
		SetPosition((float)x, (float)y);
	}

	inline void Translate(Vector2f amt)
	{
		position += amt;
	}

	inline void SetCollisionFlag(uint32_t flag)
	{
		colFlags |= flag;
	}

	inline Vector2f& GetVelocity()
	{
		return velocity;
	}

	inline bool IsPassable()
	{
		return passable;
	}

	virtual void Update(Level*, float) {}
	void Draw(sf::RenderWindow& window);
};
