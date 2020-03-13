#pragma 

#include "Entity.h"
#include "Player.h"
#include "Assets.h"
#include "Items.h"

//Color(11, 89, 87)
class Chest : public DynamicEntity 
{
	Player* player;
	Inventory* invent;
	bool IsChestOpen = false;
	sf::Sprite ChestContents;
	float dist;
	bool IsChestContentOpen = false;
	sf::Sprite ChestImage;
	Items* item = new Items();
	Sprite itemsInChest[9];
	//gives positions for first three chest item positions
	int positions[3][2] = { {350, 215}, {490, 215}, {630, 215} };
	bool itemTaken[9];

//Position for item place 1 : sf::Vector2f(357, 215)
//Position for item place 2 : sf::Vector2f(492, 215)
//Position for item place 3 : sf::Vector2f(627, 215)
//Position for item place 4 : sf::Vector2f(357, 320)
//Position for item place 5 : sf::Vector2f(492, 320)
//Position for item place 6 : sf::Vector2f(627, 320)
//Position for item place 7 : sf::Vector2f(357, 215)
//Position for item place 8 : sf::Vector2f(492, 215)
//Position for item place 9 : sf::Vector2f(627, 215)

public:
	Chest() 
	{
		//chooses random from Items
		//right now only three so chooses all three of them
		itemsInChest[0] = item->Item[randomInRange(0, 2)];
		itemsInChest[1] = item->Item[randomInRange(0, 2)];
		itemsInChest[2] = item->Item[randomInRange(0, 2)];
		itemsInChest[0].setPosition(sf::Vector2f(positions[0][0],positions[0][1]));
		itemTaken[0] = false;
		itemsInChest[1].setPosition(sf::Vector2f(positions[1][0], positions[1][1]));
		itemTaken[1] = false;
		itemsInChest[2].setPosition(sf::Vector2f(positions[2][0], positions[2][1]));
		itemTaken[2] = false;
		LoadTexture(ChestContents, "Assets/ChestInterface.png");
		ChestContents.setPosition(Vector2f(260, 100));
	}

	void spawn(Player* player, Inventory* inventory, int type, int x, int y);

	void Update(Level* level, float elapsed) override;

	void open();

	void Draw(Renderer& rend) override;
};
