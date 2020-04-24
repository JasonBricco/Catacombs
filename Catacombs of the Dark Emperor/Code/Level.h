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

	int destroyCount = 0;
	Entity* pendingDestroy[256000];

	bool restartPending;
	float restartTime = 0.0f;

	sf::RectangleShape blackscreen;
	sf::RectangleShape resumeButton;
	sf::RectangleShape mainMenuButton;
	sf::RectangleShape restartGameButton;
	sf::RectangleShape startGameButton;

	Text title;
	Text gameOverText;
	Text restartText;
	Text gamePaused;
	Text resume;
	Text mainMenu;
	Text restartButtonText;
	Text startGameText;
	Text scoreText;
	Text youDidIt;
	Text defeated;
	Assets* assets = Assets::Instance();
	Font& font = assets->GetFont("Assets/Hylia.ttf");
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
		if (!entity->pendingDestroy)
		{
			entity->pendingDestroy = true;
			pendingDestroy[destroyCount++] = entity;
		}
	}

	inline void Restart(float time)
	{
		if (score == topscore)
		{
			setTopScore();
		}
		restartTime = time;
		restartPending = true;
		score = 0;
	}

	void Update(float elapsed);
	void Draw(Renderer& rend);

	void Destroy();

	void DrawGamePauseScreen(Renderer& rend);

	void DrawGameOverScreen(Renderer& rend);

	void DrawGameStartScreen(Renderer& rend);

	void DrawGameFinishedScreen(Renderer& rend);

};

