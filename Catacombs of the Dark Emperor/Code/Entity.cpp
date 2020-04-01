#include "Stdafx.h"
#include "Entity.h"
#include "Assets.h"
#include "Utils.h"
#include "Level.h"
#include "Collision.h"
#include "Globals.h"

Entity::Entity(std::string name)
{
	LoadTexture(sprite, name);
}

void Entity::Damage(Level* level, int amount, Vector2f knockback)
{
	if (invincibleTime <= 0.0f)
	{
		health = std::max(health - amount, 0);

		if (health == 0)
			Kill(level);
		else
		{
			// Invincible frames.
			invincibleTime = 0.1f;

			tint = Color(255, 0, 0, 255);
			tintTime = 0.05f;

			if (knockback.x != 0.0f || knockback.y != 0.0f)
			{
				// If this entity is a dynamic entity, apply knockback
				// based on the force passed in.
				DynamicEntity* dyn = dynamic_cast<DynamicEntity*>(this);

				if (dyn != nullptr)
					dyn->Knockback(knockback);
			}
		}
	}
}

// Default kill simply destroys the entity.
void Entity::Kill(Level* level)
{
	level->DestroyEntity(this);
}

void Entity::LoadTexture(Sprite& spriteToSet, std::string name)
{
	Assets* assets = Assets::Instance();
	sf::Texture& tex = assets->GetTexture(name);

	spriteToSet.setTexture(tex);
	Vector2u texSize = tex.getSize();

	// By default, use the size of the image to figure out
	// collision size.
	size = Vector2f((float)texSize.x, (float)texSize.y) / PIXELS_PER_UNIT;
}

void Entity::Draw(Renderer& rend)
{
	// Multiply the world position by PIXELS_PER_UNIT to
	// get the pixel location to draw at.
	Vector2f drawP = position * PIXELS_PER_UNIT;

	sprite.setColor(tint);

	sprite.setPosition(drawP);
	rend.Draw(&sprite, layer);
}

void Entity::DrawOutline(Renderer& rend)
{
	// Draw outlines for entities that collide.
	if (collideType != CollideType::Passable)
	{
		outline = RectangleShape(size * PIXELS_PER_UNIT);
		outline.setOutlineThickness(-2.0f);
		outline.setPosition((GetPosition() + offset) * PIXELS_PER_UNIT);
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(Color::Green);
		rend.Draw(&outline, INT_MAX);
	}
}

void DynamicEntity::Move(Level* level, Vector2f accel, float elapsed)
{
	accel *= speed;
	accel += velocity * -16.0f;

	// Using the following equations of motion:

	// - p' = 1/2at^2 + vt + p.
	// - v' = at + v.
	// - a = specified by input.

	// Where a = acceleration, v = velocity, and p = position.
	// v' and p' denote new versions, while non-prime denotes old.

	// These are found by integrating up from acceleration to velocity. Use derivation
	// to go from position down to velocity and then down to acceleration to see how 
	// we can integrate back up.
	Vector2f delta = accel * 0.5f * Square(elapsed) + velocity * elapsed;
	velocity = accel * elapsed + velocity;

	colFlags = CF_NONE;

	Room* room = level->GetCurrentRoom();

	// Consider all other entities in this room except
	// this entity itself for collision.
	for (Entity* entity : room->GetEntities())
	{
		if (entity != this)
		{
			CollideType otherCollide = entity->GetCollideType();

			if (otherCollide == CollideType::Solid)
			{
				AABB bb = entity->BoundingBox();
				collides.push_back(bb);
			}
			else if (otherCollide == CollideType::Overlap)
			{
				AABB bb = entity->BoundingBox();

				if (TestOverlap(BoundingBox(), bb))
					overlaps.push_back(std::make_pair(entity, bb));
			}
		}
	}

	std::sort(collides.begin(), collides.end(), [this](auto a, auto b)
	{
		float distA = Distance2(a.center, position);
		float distB = Distance2(b.center, position);
		return distA < distB;
	});

	CollisionStep(this, delta, collides);

	HandleOverlaps(level);

	collides.clear();
	overlaps.clear();
}

