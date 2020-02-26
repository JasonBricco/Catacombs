#pragma 

#include "Entity.h"
#include "Player.h"

class Chest : public DynamicEntity 
{
	Player* player;

public:
	Chest() 
	{
		LoadTexture(sprites[DOWN], "Assets/redchestclosed.png");
		LoadTexture(sprites[UP], "Assets/redchestopen.png");
		sprite = sprites[DOWN];
	}

	void spawn(Player* player);

	void Update(Level* level, float elapsed) override;

	void open();
};