#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class TextureID {
	nothing,
	blank,
	button,
	list,

};


// Singleton Asset Manager
class AssetManager
{
private:
	std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::unordered_map<TextureID, std::string> m_texturePathMap;
	AssetManager();
	AssetManager(AssetManager&) = delete;
	AssetManager& operator=(AssetManager&) = delete;
public:

	inline static AssetManager& instance();
	static sf::Texture& getTexture(TextureID id);
private:
	void init();
};

