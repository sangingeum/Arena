#include "AssetManager.hpp"

AssetManager::AssetManager() {
	init();
}

AssetManager& AssetManager::instance() {
	static AssetManager manager;
	return manager;
}

sf::Texture& AssetManager::getTexture(TextureID id) {
	auto& textureMap = instance().m_textureMap;
	auto& texturePathMap = instance().m_texturePathMap;
	if (textureMap.find(id) == textureMap.end()) {
		textureMap[id] = std::make_unique<sf::Texture>();
		textureMap[id]->loadFromFile(texturePathMap[id]);
		textureMap[id]->setSmooth(true);
	}
	return *textureMap[id];
}

void AssetManager::init() {
	m_texturePathMap[TextureID::button] = "asset/image/craftpix/button.png";
	m_texturePathMap[TextureID::list] = "asset/image/craftpix/list.png";
	m_texturePathMap[TextureID::blank] = "asset/image/blank.PNG";

}
