#pragma once

class Assets
{
	// A hash table that maps a name to a resource. If a resource is requested that 
	// isn't in the table, the resource is loaded from disk. Otherwise we return the 
	// requested resource. This allows sharing resources without loading them multiple times.
	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, Font> fonts;

	// Singleton instance.
	static Assets* instance;

public:
	static inline Assets* Instance()
	{
		if (instance == nullptr)
			instance = new Assets();

		return instance;
	}

	Texture& GetTexture(std::string name);
	Font& GetFont(std::string name);
};
