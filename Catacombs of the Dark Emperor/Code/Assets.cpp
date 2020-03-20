
#include "Stdafx.h"
#include "Assets.h"
#include "Utils.h"

Assets* Assets::instance = nullptr;

Texture& Assets::GetTexture(std::string name)
{
	// Returns an iterator pointing to the found element
	// of the hash table. If this equals textures.end(),
	// it means the item does not exist in the table.
	auto it = textures.find(name);

	if (it == textures.end())
	{
		Texture tex;

		if (!tex.loadFromFile(name))
			Print("Failed to load texture %s.", name.c_str());

		textures.insert(std::make_pair(name, tex));
		return textures[name];
	}

	// it->first is the key (name), and it->second is the value (the texture).
	return it->second;
}

Font& Assets::GetFont(std::string name)
{
	auto it = fonts.find(name);

	if (it == fonts.end())
	{
		Font font;

		if (!font.loadFromFile(name))
			Print("Failed to load font %s.", name.c_str());

		fonts.insert(std::make_pair(name, font));
		return fonts[name];
	}

	return it->second;
}
