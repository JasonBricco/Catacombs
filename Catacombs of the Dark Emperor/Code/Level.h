#pragma once

#include "Room.h"

// In order to use sf::Vector2i as a key in an std::unordered_map, 
// a hash function and comparison function must be provided.
// The Vector2iHash and Vector2iCompare structures provide this. 
// They are passed as template parameters when declaring the map.
struct Vector2iHash
{
    int operator()(Vector2i v) const
    {
		return v.y * 31 + v.x;
    }
};

struct Vector2iCompare
{
    bool operator()(Vector2i a, Vector2i b) const
    {
		return a.x == b.x && a.y == b.y;
    }
};

typedef std::unordered_map<Vector2i, Room*, Vector2iHash, Vector2iCompare> RoomMap;
typedef std::unordered_set<Vector2i, Vector2iHash, Vector2iCompare> Vector2iSet;

class Level
{
	// Stores all rooms in the level using sparse storage.
	// Maps the room's position (in room coordinates) to the
	// room instance.
	RoomMap rooms;

	// The currently loaded room that is displayed.
	Room* currentRoom;

public:
	// Creates a new room at the given room coordinates.
	// If the room already exists, a new room won't be
	// created. Returns the new or existing room.
	Room* GetOrCreateRoom(int x, int y);

	inline Room* GetCurrentRoom()
	{
		return currentRoom;
	}

	inline void SetCurrentRoom(Room* room)
	{
		currentRoom = room;
	}

	void Update(float elapsed);
	void Draw(RenderWindow& window);
};
