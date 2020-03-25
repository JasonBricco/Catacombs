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
	float dist = 100.0f;
	bool IsChestContentOpen = false;
	int NumberOfItemsToAppear = 0;
	sf::Sprite ChestImage;
	Items* item = new Items();
	Sprite itemsInChest[9];
	bool itemTaken[9];
	const float cellSizeX = 135.0f;
	const float cellSizeY = 100.0f;
	const int cellCount = 3;
	int ItemNumber[9];
	float gridStartX = 355.0f;
	float gridStartY = 220.0f;

public:
	Chest() 
	{
		Vector2i gridP = Vector2i(0, 0);
		NumberOfItemsToAppear = randomInRange(1, 9);
		for (int i = 0 ; i < NumberOfItemsToAppear ; i++)
		{
			ItemNumber[i] = randomInRange(0, 2);
			itemsInChest[i] = item->Item[ItemNumber[i]];
			float x = gridStartX + gridP.x * cellSizeX;
			float y = gridStartY + gridP.y * cellSizeY;

			itemsInChest[i].setPosition(x, y);
			itemTaken[i] = false;

			++gridP.x;

			if (gridP.x == cellCount)
			{
				gridP.x = 0;
				++gridP.y;
			}
		}
		LoadTexture(ChestContents, "Assets/ChestInterface.png");
		ChestContents.setPosition(Vector2f(260, 100));
	}

	void spawn(Player* player, int type, int x, int y);

	void Update(Level* level, float elapsed) override;

	void open();

	void Draw(Renderer& rend) override;
};
