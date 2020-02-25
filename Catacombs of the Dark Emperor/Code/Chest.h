#pragma 

#include "Entity.h"

class Chest : public DynamicEntity {

public:

	Chest() 
	{
		LoadTexture(sprites[DOWN], "Assets/redchestclosed.png");
		LoadTexture(sprites[UP], "Assets/redchestopen.png");
		sprite = sprites[DOWN];
	}

	void spawn();

	void Update(Level* level, float elapsed) override;

	void open();
};