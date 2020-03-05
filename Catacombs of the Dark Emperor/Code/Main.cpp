#include "Stdafx.h"
#include "Player.h"
#include "Level.h"
#include "Generator.h"

int main(int, char**)
{
	uint32_t seed = (uint32_t)time(NULL);
	srand(seed);

	Print("Level seed: %u\n", seed);

	int width = 1024, height = 608;

	RenderWindow window(VideoMode(width, height), "Catacombs of the Dark Emperor");
	window.setVerticalSyncEnabled(true);

	Renderer rend(&window);

	Level* level = new Level();

	LevelGenerator* generator = new LevelGenerator();
	generator->Build(level);

	// Tracks frame time so we can use it for updating entities
	// in a framerate independent manner.
	Clock clock;
	Time elapsed;

	// Game loop.
	while (window.isOpen())
	{
		Event event;

		// Loop through window events and respond to them. 
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// Clear the screen to a black color.
		window.clear(Color::Black);

		level->Update(elapsed.asSeconds());
		level->Draw(rend);

		rend.WriteToWindow();
		window.display();

		elapsed = clock.restart();
	}

	return 0;
}
