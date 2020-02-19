// 
// Catacombs of the Dark Emperor
//

#include "Stdafx.h"
#include "Player.h"
#include "iostream"

int main(int, char**)
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Catacombs of the Dark Emperor");
	window.setVerticalSyncEnabled(true);

	Player player = Player();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		{
			// 1 is for up
			player.move(1);
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// 2 is for left
			player.move(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// 3 is for down
			player.move(3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// 4 is for right
			player.move(4);
		}

		player.Draw(window);

		window.display();
	}

	return 0;
}
