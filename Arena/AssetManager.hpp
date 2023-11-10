#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

enum class TextureID {
	nothing,
	button,
	list
};

class AssetManager
{
private:
	std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::unordered_map<TextureID, std::string> m_texturePathMap;
public:
	AssetManager() {
		init();
	}
	sf::Texture& getTexture(TextureID id) {
		if (m_textureMap.find(id) == m_textureMap.end()) {
			m_textureMap[id] = std::make_unique<sf::Texture>();
			m_textureMap[id]->loadFromFile(m_texturePathMap[id]);
			m_textureMap[id]->setSmooth(true);
		}
		return *m_textureMap[id];
	}
private:

	void init() {
		m_texturePathMap[TextureID::button] = "asset/image/craftpix/button.png";
		m_texturePathMap[TextureID::list] = "asset/image/craftpix/list.png";

	}
};

