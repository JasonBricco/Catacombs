#pragma 

#include "Entity.h"
#include "Player.h"

class Chest : public DynamicEntity 
{
	Player* player;
	bool IsChestOpen = false;
	sf::RectangleShape ChestContents;
	float dist;
	bool IsChestContentOpen = false;

public:
	Chest() 
	{
		ChestContents.setSize(sf::Vector2f(800, 390));
		ChestContents.setPosition(Vector2f(100, 100));
		ChestContents.setFillColor(Color::Black);
		ChestContents.setOutlineThickness(10);
		ChestContents.setOutlineColor(Color::Yellow);
	}

	void spawn(Player* player, int type);

	void Update(Level* level, float elapsed) override;

	void open();

	void Draw(RenderWindow& window) override;
};