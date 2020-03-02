#pragma once

#include "Collision.h"

class Level;

enum class CollideType
{
	Passable,
	Overlap,
	Solid
};

// For use in collision detection, to identify an identity type.
// Entities that don't need to be detected don't need an entry here.
enum class EntityID
{
	None,
	DoorUp,
	DoorDown,
	DoorLeft,
	DoorRight
};

class Entity
{
protected:
	EntityID id = EntityID::None;
	Sprite sprite;

	bool visible = true;

	// Size is used for collision. It's the size in world units. A 32x32 pixel
	// entity would have a size here of 1x1. Offset is the relative position 
	// from the entity's pivot point for the collision box to be.
	Vector2f size, position;

	Vector2f offset = {};

	// Whether this entity will be collided with.
	CollideType collideType = CollideType::Solid;

	void LoadTexture(Sprite& sprite, std::string name);

public:
	// Name is the name of the texture to load for this entity.
	// By default, the pivot is the upper-left corner. 
	Entity(std::string name);

	Entity() {}
	
	inline EntityID ID()
	{
		return id;
	}

	inline AABB BoundingBox()
	{
		return AABBFromCorner(position + offset, size);
	}

	inline bool Visible()
	{
		return visible;
	}

	inline void SetPosition(float x, float y)
	{
		position = Vector2f(x, y);
	}

	inline void SetPosition(int x, int y)
	{
		SetPosition((float)x, (float)y);
	}

	inline const Vector2f GetPosition()
	{
		return position;
	}

	inline CollideType GetCollideType()
	{
		return collideType;
	}

	inline bool IsPassable()
	{
		return collideType == CollideType::Passable || collideType == CollideType::Overlap;
	}

	virtual void Update(Level*, float) {}
	void Draw(sf::RenderWindow& window);
};

class DynamicEntity : public Entity
{
protected:
	// Contains a sprite for each facing direction.
	Sprite sprites[4];

	// Temporary storage to store bounding boxes we have to check for collision. 
	// It's static because only one entity will utilize it at a time.
	// This is more efficient for memory.
	static std::vector<AABB> collides;
	static std::vector<std::pair<Entity*, AABB>> overlaps;

	Vector2f velocity = {};

	float speed = 0.0f;

	// Tracks on which sides this entity collided during the 
	// last collision step.
	uint32_t colFlags = CF_NONE;

	virtual void HandleOverlaps(Level*) {}

public:
	DynamicEntity() : Entity() {}

	// Moves the entity based on the set acceleration.
	void Move(Level* level, Vector2f accel, float elapsed);

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
};
