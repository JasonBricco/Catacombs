#pragma once

class Entity;

enum CollisionFlags : uint32_t
{
	CF_NONE = 0,
	CF_UP = 1,
	CF_DOWN = 2,
	CF_LEFT = 4,
	CF_RIGHT = 8
};

struct AABB
{
	Vector2f center;
	Vector2f radius;

	inline Vector2f BottomLeft()
	{
		return center - radius;
	}

	inline Vector2f TopRight()
	{
		return center + radius;
	}

	inline void Expand(Vector2f amount)
	{
		radius += amount;
	}

	inline void Shrink(Vector2f amount)
	{
		radius -= amount;
	}
};

void CollisionStep(Entity* entity, Vector2f delta, std::vector<AABB>& collides);

// Helper functions to create AABBs.
// These are used instead of constructors since
// they all take exactly the same types of arguments.

AABB AABBFromCorner(Vector2f corner, Vector2f size);
AABB AABBFromMinMax(Vector2f min, Vector2f max);
AABB AABBFromCenter(Vector2f center, Vector2f radius);
AABB AABBFromBottomCenter(Vector2f bc, Vector2f size);
