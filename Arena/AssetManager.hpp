#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class TextureID {
	nothing,
	button,
	list
};


// Singleton Asset Manager
class AssetManager
{
private:
	std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::unordered_map<TextureID, std::string> m_texturePathMap;
	AssetManager() {
		init();
	}
	AssetManager(AssetManager&) = delete;
	AssetManager& operator=(AssetManager&) = delete;
public:

	inline static AssetManager& instance() {
		static AssetManager manager;
		return manager;
	}
	static sf::Texture& getTexture(TextureID id) {
		auto& textureMap = instance().m_textureMap;
		auto& texturePathMap = instance().m_texturePathMap;
		if (textureMap.find(id) == textureMap.end()) {
			textureMap[id] = std::make_unique<sf::Texture>();
			textureMap[id]->loadFromFile(texturePathMap[id]);
			textureMap[id]->setSmooth(true);
		}
		return *textureMap[id];
	}
private:
	void init() {
		m_texturePathMap[TextureID::button] = "asset/image/craftpix/button.png";
		m_texturePathMap[TextureID::list] = "asset/image/craftpix/list.png";

	}
};

