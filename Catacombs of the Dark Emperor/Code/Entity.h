#pragma once

#include "Collision.h"
#include "Renderer.h"

class Level;

// Represents a sprite sheet for animation.
// For simplicity, we'll assume our sprite sheets
// are only on a single row (not multiple rows). All the
// ones we'll use follow this.
struct AnimationClip
{
	Sprite frames;
	int frameCount;
	Vector2i frameSize;
	bool wait;
	float fps;
	int frame;
	float interval;
	float timeLeft;
	bool finished;

	// Play the animation backwards (for flipped sheets).
	bool backwards;
};

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
	Player,
	DoorUp,
	DoorDown,
	DoorLeft,
	DoorRight,
	DoorStairsUp,
	DoorStairsDown,
	Enemy
};

class Entity
{
protected:
	EntityID id = EntityID::None;
	Sprite sprite;

	// Debug outline.
	RectangleShape outline;

	int health = 16;
	int maxHealth = 16;

	float invincibleTime = 0.0f;

	// For modifying entity colors.
	Color tint = Color::White;
	float tintTime = 0.0f;

	bool visible = true;

	// Size is used for collision. It's the size in world units. A 32x32 pixel
	// entity would have a size here of 1x1. Offset is the relative position 
	// from the entity's pivot point for the collision box to be.
	Vector2f size, position;

	bool resistKnockback = false;

	// Rendering layer. Entities with a higher layer draw in front of 
	// entities with a lower layer.
	int layer = 0;

	Vector2f offset = {};

	// Whether this entity will be collided with.
	CollideType collideType = CollideType::Solid;

	void LoadTexture(Sprite& sprite, string name);

public:
	bool pendingDestroy = false;

	// Name is the name of the texture to load for this entity.
	// By default, the pivot is the upper-left corner. 
	Entity(string name);

	Entity() {}
	
	inline EntityID ID()
	{
		return id;
	}

	inline void FullyHeal()
	{
		health = maxHealth;
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

	inline void SetCentered(float x, float y)
	{
		position = Vector2f(x, y);
		position.x -= size.x * 0.5f;
		position.y -= size.y * 0.5f;
	}

	inline void SetPosition(int x, int y)
	{
		SetPosition((float)x, (float)y);
	}

	inline Vector2f GetPosition()
	{
		return position;
	}

	inline Vector2f GetCenter()
	{
		return BoundingBox().center;
	}

	inline Vector2f GetSize()
	{
		return size;
	}

	inline CollideType GetCollideType()
	{
		return collideType;
	}

	inline bool IsPassable()
	{
		return collideType == CollideType::Passable || collideType == CollideType::Overlap;
	}

	inline Sprite* GetSprite()
	{
		return &sprite;
	}

	virtual void Damage(Level* level, int amount, Vector2f knockback = Vector2(0.0f, 0.0f));
	virtual void Kill(Level* level);

	virtual void Update(Level*, float elapsed) 
	{
		invincibleTime -= elapsed;
		tintTime -= elapsed;

		if (tintTime <= 0.0f)
			tint = Color::White;
	}

	virtual void Draw(Renderer& rend);
	void DrawOutline(Renderer& rend);
};

class DynamicEntity : public Entity
{
protected:
	// Contains a sprite for each facing direction.
	Sprite sprites[4];

	// Facing direction.
	int facing;

	// Animations.
	AnimationClip move[4];
	AnimationClip attack[4];

	// Current animation clip.
	AnimationClip* anim = nullptr;

	// Temporary storage to store bounding boxes we have to check for collision. 
	// It's static because only one entity will utilize it at a time.
	// This is more efficient for memory.
	static inline std::vector<AABB> collides;
	static inline std::vector<std::pair<Entity*, AABB>> overlaps;

	Vector2f velocity = {};

	float speed = 0.0f;

	// Tracks on which sides this entity collided during the 
	// last collision step.
	uint32_t colFlags = CF_NONE;

	void SetFacing(Vector2f accel);

	virtual void HandleOverlaps(Level*) {}

	void CreateClip(AnimationClip* arr, int slot, Sprite frames, Vector2i frameSize, int frameCount, float fps, bool wait, bool backwards = false);
	void SetAnimation(AnimationClip* clip);
	void ComputeAnimation(float elapsed);

public:
	DynamicEntity() : Entity() {}

	// Moves the entity based on the set acceleration.
	void Move(Level* level, Vector2f accel, float elapsed);

	virtual void HandleCollide(Level*) {}

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

	inline Sprite* GetSprites()
	{
		return sprites;
	}

	inline void Knockback(Vector2f force)
	{
		velocity = force;
	}
};
