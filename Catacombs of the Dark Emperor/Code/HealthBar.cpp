#include "Stdafx.h"
#include "HealthBar.h"

void HealthBar::UpdateHearts(int health)
{
	for (int i = 0; i < 8; i++)
	{
		Sprite* heartSprite = hearts[i]->GetSprite();
		Sprite* heartSprites = hearts[i]->GetSprites();
		if (health < (2 * i) + 1)
		{
			*heartSprite = heartSprites[2];
		}
		else if (health == (2 * i) + 1)
		{
			*heartSprite = heartSprites[1];
		}
		else
		{
			*heartSprite = heartSprites[0];
		}
	}

}

