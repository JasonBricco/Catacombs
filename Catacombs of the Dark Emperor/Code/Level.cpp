
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
			getGameState().gameFinished = false;
		}
	}
}

void Level::Draw(Renderer& rend)
{
	assert(currentRoom != nullptr);
	currentRoom->Draw(rend);
	if (getGameState().gameOver)
	{
		DrawGameOverScreen(rend);
	}

	if (getGameState().gameStart)
	{
		getGameState().paused = true;
		DrawGameStartScreen(rend);
	}
	else if (getGameState().manualPause)
	{
		DrawGamePauseScreen(rend);
	}
	else if (getGameState().gameFinished)
	{
		DrawGameFinishedScreen(rend);
	}

	if (Mouse::isButtonPressed(Mouse::Left) && getGameState().gameStart)
	{
		if (startGameButton.getGlobalBounds().contains(rend.getWindow()->mapPixelToCoords(Mouse::getPosition(*rend.getWindow()))))
		{
			getGameState().paused = false;
			getGameState().gameStart = false;
			getGameState().manualPause = false;
			Restart(0.0f);
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left) && getGameState().manualPause)
	{
		if (resumeButton.getGlobalBounds().contains(rend.getWindow()->mapPixelToCoords(Mouse::getPosition(*rend.getWindow()))))
		{
			getGameState().paused = false;
			getGameState().manualPause = false;
		}
		else if (restartGameButton.getGlobalBounds().contains(rend.getWindow()->mapPixelToCoords(Mouse::getPosition(*rend.getWindow()))))
		{
			Restart(0.0f);
			getGameState().paused = false;
			getGameState().manualPause = false;
		}
		else if (mainMenuButton.getGlobalBounds().contains(rend.getWindow()->mapPixelToCoords(Mouse::getPosition(*rend.getWindow()))))
		{
			getGameState().gameStart = true;
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left) && getGameState().gameFinished)
	{
		if (mainMenuButton.getGlobalBounds().contains(rend.getWindow()->mapPixelToCoords(Mouse::getPosition(*rend.getWindow()))))
		{
			getGameState().gameStart = true;
			getGameState().gameFinished = false;
		}
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

void Level::DrawGamePauseScreen(Renderer& rend)
{
	gamePaused = Text("Game Paused", font, 50);
	gamePaused.setFillColor(sf::Color::Yellow);
	gamePaused.setPosition(24.5 * 32 / 2, 5 * 32 / 2);
	gamePaused.setStyle(sf::Text::Bold);

	blackscreen.setSize(Vector2f(32 * 32, 19 * 32));
	blackscreen.setPosition(0, 0);
	blackscreen.setFillColor(Color::Black);

	resume = Text("Resume", font, 25);
	resume.setFillColor(sf::Color::Yellow);
	resume.setPosition(31 * 32 / 2, 11 * 32 / 2);

	resumeButton.setSize(Vector2f(8 * 32, 1 * 32));
	resumeButton.setPosition(26 * 32 / 2, 11 * 32 / 2);
	resumeButton.setOutlineColor(Color::Yellow);
	resumeButton.setOutlineThickness(5);
	resumeButton.setFillColor(Color::Transparent);

	restartButtonText = Text("Restart", font, 25);
	restartButtonText.setFillColor(sf::Color::Yellow);
	restartButtonText.setPosition(31 * 32 / 2, 15 * 32 / 2);

	restartGameButton.setSize(Vector2f(8 * 32, 1 * 32));
	restartGameButton.setPosition(26 * 32 / 2, 15 * 32 / 2);
	restartGameButton.setOutlineColor(Color::Yellow);
	restartGameButton.setOutlineThickness(5);
	restartGameButton.setFillColor(Color::Transparent);

	mainMenu = Text("Main Menu", font, 25);
	mainMenu.setFillColor(sf::Color::Yellow);
	mainMenu.setPosition(30 * 32 / 2, 19 * 32 / 2);

	mainMenuButton.setSize(Vector2f(8 * 32, 1 * 32));
	mainMenuButton.setPosition(26 * 32 / 2, 19 * 32 / 2);
	mainMenuButton.setOutlineColor(Color::Yellow);
	mainMenuButton.setOutlineThickness(5);
	mainMenuButton.setFillColor(Color::Transparent);

	rend.Draw(&mainMenu, 135);
	rend.Draw(&resume, 135);
	rend.Draw(&restartButtonText, 135);
	rend.Draw(&mainMenuButton, 134);
	rend.Draw(&resumeButton, 134);
	rend.Draw(&restartGameButton, 134);
	rend.Draw(&gamePaused, 135);
	rend.Draw(&blackscreen, 130);
}

void Level::DrawGameOverScreen(Renderer& rend)
{
	gameOverText = Text("Game Over!", font, 40);
	gameOverText.setFillColor(sf::Color::Yellow);
	gameOverText.setPosition(25 * 32 / 2, 15 * 32 / 2);
	gameOverText.setStyle(sf::Text::Bold);

	restartText = Text("Restarting . . .", font, 30);
	restartText.setFillColor(sf::Color::Yellow);
	restartText.setPosition(26 * 32 / 2, 21 * 32 / 2);

	blackscreen.setSize(Vector2f(32 * 32, 19 * 32));
	blackscreen.setPosition(0, 0);
	blackscreen.setFillColor(Color::Black);

	rend.Draw(&restartText, 135);
	rend.Draw(&gameOverText, 135);
	rend.Draw(&blackscreen, 130);
}

void Level::DrawGameStartScreen(Renderer& rend)
{
	blackscreen.setSize(Vector2f(32 * 32, 19 * 32));
	blackscreen.setPosition(0, 0);
	blackscreen.setFillColor(Color::Black);

	title = Text("Catacombs of the Dark Emperor", font, 40);
	title.setFillColor(sf::Color::Yellow);
	title.setPosition(15 * 32 / 2, 25 * 32 / 2);
	title.setStyle(sf::Text::Bold);

	startGameText = Text("Start Game", font, 25);
	startGameText.setFillColor(sf::Color::Yellow);
	startGameText.setPosition(30 * 32 / 2, 31 * 32 / 2);

	startGameButton.setSize(Vector2f(8 * 32, 1 * 32));
	startGameButton.setPosition(26 * 32 / 2, 31 * 32 / 2);
	startGameButton.setOutlineColor(Color::Yellow);
	startGameButton.setOutlineThickness(5);
	startGameButton.setFillColor(Color::Transparent);

	rend.Draw(&blackscreen, 130);
	rend.Draw(&title, 135);
	rend.Draw(&startGameButton, 135);
	rend.Draw(&startGameText, 135);
}

void Level::DrawGameFinishedScreen(Renderer& rend)
{
	youDidIt = Text("You Did It!", font, 40);
	youDidIt.setFillColor(sf::Color::Yellow);
	youDidIt.setPosition(25 * 32 / 2, 15 * 32 / 2);
	youDidIt.setStyle(Text::Bold);

	defeated = Text("The Dark Emperor was Defeated.", font, 30);
	defeated.setFillColor(sf::Color::Yellow);
	defeated.setPosition(18 * 32 / 2, 18 * 32 / 2);

	scoreText = Text("Your Score: ", font, 30);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setPosition(25 * 32 / 2, 21 * 32 / 2);
	scoreText.setString("Your Score: " + std::to_string(score));

	mainMenu = Text("Main Menu", font, 25);
	mainMenu.setFillColor(sf::Color::Yellow);
	mainMenu.setPosition(28 * 32 / 2, 28 * 32 / 2);
	
	mainMenuButton.setSize(Vector2f(8 * 32, 1 * 32));
	mainMenuButton.setPosition(24 * 32 / 2, 28 * 32 / 2);
	mainMenuButton.setOutlineColor(Color::Yellow);
	mainMenuButton.setOutlineThickness(5);
	mainMenuButton.setFillColor(Color::Transparent);

	blackscreen.setSize(Vector2f(32 * 32, 19 * 32));
	blackscreen.setPosition(0, 0);
	blackscreen.setFillColor(Color::Black);

	rend.Draw(&defeated, 135);
	rend.Draw(&mainMenu, 135);
	rend.Draw(&mainMenuButton, 134);
	rend.Draw(&youDidIt, 135);
	rend.Draw(&scoreText, 135);
	rend.Draw(&blackscreen, 130);
}
