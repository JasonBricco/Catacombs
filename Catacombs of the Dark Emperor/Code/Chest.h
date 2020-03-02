#pragma 

#include "Entity.h"
#include "Player.h"
#include "Assets.h"


//Color(11, 89, 87)
class Chest : public DynamicEntity 
{
	Player* player;
	bool IsChestOpen = false;
	sf::Sprite ChestContents;
	float dist;
	bool IsChestContentOpen = false;
	sf::Sprite ChestImage;

public:
	Chest() 
	{
		LoadTexture(ChestContents, "Assets/ChestInterfaceFull.png");
		ChestContents.setPosition(Vector2f(100, 100));
	}

	void spawn(Player* player, int type);

	void Update(Level* level, float elapsed) override;

	void open();

	void Draw(RenderWindow& window) override;
};