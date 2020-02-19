// 
// Catacombs of the Dark Emperor
//

#include "Stdafx.h"
#include "Player.h"
#include "Level.h"
#include "Generator.h"

int main(int, char**)
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Catacombs of the Dark Emperor");
	window.setVerticalSyncEnabled(true);

	Level* level = new Level();

	BasicGenerator* generator = new BasicGenerator();
	generator->Build(level);

	// Tracks frame time so we can use it for updating entities
	// in a framerate independent manner.
	sf::Clock clock;
	sf::Time elapsed;

	// Game loop.
	while (window.isOpen())
	{
		sf::Event event;

		// Loop through window events and respond to them. 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Clear the screen to a black color.
		window.clear(sf::Color::Black);

		level->Update(elapsed.asSeconds());
		level->Draw(window);

		window.display();

		elapsed = clock.restart();
	}

	return 0;
}
