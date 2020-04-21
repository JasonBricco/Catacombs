#pragma once

#include "Room.h"
#include "Assets.h"

class Level
{
	// Stores all rooms in the level using sparse storage.
	// Maps the room's position (in room coordinates) to the
	// room instance.
	RoomMap rooms;

	// The currently loaded room that is displayed.
	Room* currentRoom;

	vector<Entity*> pendingDestroy;

	bool restartPending;
	float restartTime = 0.0f;

	sf::RectangleShape gameover;

	Text gameOverText;
	Text restartText;
	Assets* assets = Assets::Instance();
	Font& font = assets->GetFont("Assets/Arial.ttf");
	String restarting;
	int rest = 0;

public:
	// Creates a new room at the given room coordinates.
	// If the room already exists, a new room won't be
	// created. Returns the new or existing room.
	Room* GetOrCreateRoom(int x, int y);

	Room* GetRoom(Vector2i p);

	inline Room* GetRoom(int x, int y)
	{
		return GetRoom(Vector2i(x, y));
	}

	inline Room* GetCurrentRoom()
	{
		return currentRoom;
	}

	inline RoomMap& GetRooms()
	{
		return rooms;
	}

	inline void SetCurrentRoom(Room* room)
	{
		currentRoom = room;
	}

	inline void DestroyEntity(Entity* entity)
	{
		pendingDestroy.push_back(entity);
	}

	inline void Restart(float time)
	{
		restartTime = time;
		restartPending = true;
	}

	void Update(float elapsed);
	void Draw(Renderer& rend);

	void Destroy();
};
