#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class TextureID {
	nothing,
	// UI
	blank,
	button,
	list,
	// Shinobi
	Shinobi_Attack_1,
	Shinobi_Attack_2,
	Shinobi_Attack_3,
	Shinobi_Dead,
	Shinobi_Hurt,
	Shinobi_Idle,
	Shinobi_Jump,
	Shinobi_Run,
	Shinobi_Shield,
	Shinobi_Walk,
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

