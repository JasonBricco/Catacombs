
#include "Stdafx.h"
#include "Entity.h"
#include "Assets.h"

Entity::Entity(std::string name)
{
	Assets* assets = Assets::Instance();
	sf::Texture& tex = assets->GetTexture(name);

	sprite.setTexture(tex);
}

void Entity::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}
