
#include "Stdafx.h"
#include "Collision.h"
#include "Level.h"
#include "Utils.h"
#include "Globals.h"

static float Get(Vector2f v, int index)
{
	return index == 0 ? v.x : v.y;
}

AABB AABBFromCorner(Vector2f corner, Vector2f size)
{
	AABB bb;
	bb.radius = size * 0.5f;
	bb.center = corner + bb.radius;
	return bb;
}

AABB AABBFromMinMax(Vector2f min, Vector2f max)
{
	return AABBFromCorner(min, max - min);
}

AABB AABBFromCenter(Vector2f center, Vector2f radius)
{
	return { center, radius };
}

AABB AABBFromBottomCenter(Vector2f bc, Vector2f size)
{
	AABB bb;
	bb.radius = size * 0.5f;
	bb.center = Vector2f(bc.x, bc.y + bb.radius.y);
	return bb;
}

// Tests for line collision against a wall by solving for the time of collision.
// Delta is the length of the line.
// p is the position to start at.
// wallP is the wall position along the specified axis (axis0).
// wMin and wMax are wall positions of the axis we're not checking against, used for bounding.
// This function treats each wall as being infinitely long. The function will return a time
// of collision delta faces the direction of the wall regardless. We bound using wMin and wMax
// to ensure we actually collided with the visible section of wall. 
static bool TestWall(Vector2f delta, Vector2f p, float wallP, Vector2f wMin, Vector2f wMax, int axis0, int axis1, float& tMin)
{
	float delta0 = Get(delta, axis0);
	float delta1 = Get(delta, axis1);

	if (delta0 != 0.0f)
	{
		float tResult = (wallP - Get(p, axis0)) / delta0;

		if (tResult >= 0.0f && tResult < tMin)
		{
			float o1 = Get(p, axis1) + tResult * delta1;

			if (o1 >= Get(wMin, axis1) && o1 <= Get(wMax, axis1))
			{
				tMin = tResult;
				return true;
			}
		}
	}

	return false;
}

static bool TestTileCollision(Entity* entity, AABB a, AABB b, Vector2f delta, float& tMin, Vector2f& normal)
{
	bool result = false;

	// We use Minkowski algebra for collisions. In other words, shrink our entity
	// to a point and expand the entity to test against by our size. Then we 
	// have reduced the collision checking problem to a simple line test.
	b.Expand(a.radius);
	a.Shrink(a.radius);

	Vector2f wMin = b.center - b.radius, wMax = b.center + b.radius;

	// Top surface.
	if (TestWall(delta, a.center, wMax.y, wMin, wMax, 1, 0, tMin))
	{
		normal = Vector2f(0.0f, 1.0f);
		entity->SetCollisionFlag(CF_DOWN);
		result = true;
	}

	// Bottom surface.
	if (TestWall(delta, a.center, wMin.y, wMin, wMax, 1, 0, tMin))
	{
		normal = Vector2f(0.0f, -1.0f);
		entity->SetCollisionFlag(CF_UP);
		result = true;
	}

	// Right wall.
	if (TestWall(delta, a.center, wMin.x, wMin, wMax, 0, 1, tMin))
	{
		normal = Vector2f(-1.0f, 0.0f);
		entity->SetCollisionFlag(CF_RIGHT);
		result = true;
	}

	// Left wall.
	if (TestWall(delta, a.center, wMax.x, wMin, wMax, 0, 1, tMin))
	{
		normal = Vector2f(1.0f, 0.0f);
		entity->SetCollisionFlag(CF_LEFT);
		result = true;
	}

	return result;
}

void CollisionStep(Entity* entity, Vector2f delta, std::vector<AABB>& collides)
{
	float tRemaining = 1.0f;

	// Run for three iterations at most, as long as we have movement
	// remaining to do.
	for (int it = 0; it < 3 && tRemaining > 0.0f; ++it)
	{
		AABB bb = entity->BoundingBox();

		// The percentage of movement we have left to go. 1 means all of it, 0 means we're done.
		float tMin = 1.0f;

		// The vector perpendicular to the surface we collide with.
		Vector2f normal = Vector2f(0.0f, 0.0f);

		bool hit = false;

		for (AABB targetBB : collides)
		{
			bool result = TestTileCollision(entity, bb, targetBB, delta, tMin, normal);

			if (result)
				hit = true;
		}

		entity->Translate(delta * tMin);

		if (normal != Vector2f(0.0f, 0.0f))
			entity->Translate(normal * EPSILON);

		if (hit)
		{
			// Adjust velocity by removing the component of velocity
			// that collided with a wall, and retaining the other. 
			// This allows for smooth sliding along walls.
			Vector2f& velocity = entity->GetVelocity();
			velocity -= Dot(velocity, normal) * normal;
			delta -= Dot(delta, normal) * normal;
		}

		delta -= (delta * tMin);
		tRemaining -= (tMin * tRemaining);
	}
}
