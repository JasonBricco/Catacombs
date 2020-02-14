// 
// Catacombs of the Dark Emperor
//

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int, char**)
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Catacombs of the Dark Emperor");
	window.setVerticalSyncEnabled(true);

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
		window.display();
	}

	return 0;
}
