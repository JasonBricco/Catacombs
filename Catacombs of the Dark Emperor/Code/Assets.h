#pragma once

class Assets
{
	// A hash table that maps a name to a texture. If a texture is requested that 
	// isn't in the table, the texture is loaded from disk. Otherwise we return the 
	// requested texture. This allows sharing textures without loading them multiple times.
	std::unordered_map<std::string, sf::Texture> textures;

	// Singleton instance.
	static Assets* instance;

public:
	static inline Assets* Instance()
	{
		if (instance == nullptr)
			instance = new Assets();

		return instance;
	}

	sf::Texture& GetTexture(std::string name);
};
