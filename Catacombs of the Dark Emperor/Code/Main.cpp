#include "Stdafx.h"
#include "Player.h"
#include "Level.h"
#include "Generator.h"

int main(int, char**)
{
	srand((uint32_t)time(NULL));

	int width = 1024, height = 576;

	RenderWindow window(VideoMode(width, height), "Catacombs of the Dark Emperor");
	window.setVerticalSyncEnabled(true);

	Level* level = new Level();

	BasicGenerator* generator = new BasicGenerator();
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
		level->Draw(window);

		window.display();

		elapsed = clock.restart();
	}

	return 0;
}
