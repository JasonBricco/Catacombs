
#include "Stdafx.h"
#include "Level.h"

Room* Level::GetOrCreateRoom(int x, int y)
{
	Vector2i p(x, y);
	auto it = rooms.find(p);

	if (it == rooms.end())
	{
		Room* room = new Room();
		room->SetPosition(x, y);
		rooms.insert(std::make_pair(p, room));
		return room;
	}

	return it->second;
}

Room* Level::GetRoom(Vector2i p)
{
	auto it = rooms.find(p);
	assert(it != rooms.end());
	return it->second;
}

void Level::Update(float elapsed)
{
	assert(currentRoom != nullptr);
	currentRoom->Update(this, elapsed);

	// Destroy entities after updating is done,
	// so we don't destroy mid-iteration.
	for (Entity* entity : pendingDestroy)
	{
		currentRoom->RemoveEntity(entity);
		delete entity;
	}

	pendingDestroy.clear();

	if (restartPending)
	{
		restartTime -= elapsed;

		if (restartTime <= 0.0f)
		{
			getGameState().restart = true;
			restartPending = false;
			getGameState().gameOver = false;
		}
	}
}

void Level::Draw(Renderer& rend)
{
	assert(currentRoom != nullptr);
	currentRoom->Draw(rend);
	if (getGameState().gameOver)
	{
		gameOverText = Text("Game Over!", font, 40);
		gameOverText.setFillColor(sf::Color::Yellow);
		gameOverText.setPosition(25 * 32 / 2, 15 * 32 / 2);
		gameOverText.setStyle(sf::Text::Bold);

		restartText = Text("Restarting", font, 30);
		restartText.setFillColor(sf::Color::Yellow);
		restartText.setPosition(26 * 32 / 2, 18 * 32 / 2);
		restartText.setString("Restarting . . .");

		gameover.setSize(Vector2f(32 * 32, 19 * 32));
		gameover.setPosition(0, 0);
		gameover.setFillColor(Color::Black);

		rend.Draw(&restartText, 135);
		rend.Draw(&gameOverText, 135);
		rend.Draw(&gameover, 130);
	}
}

void Level::Destroy()
{
	for (auto pair : rooms)
	{
		auto entities = pair.second->GetEntities();

		for (Entity* entity : pair.second->GetEntities())
		{
			// Don't delete the player - it should always persist.
			// Remove it instead. We still reference it in the generator,
			// which will place it in the new level.
			if (entity->ID() == EntityID::Player)
				pair.second->RemoveEntity(entity);
			else delete entity;
		}
	}
}
