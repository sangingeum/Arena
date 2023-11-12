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
	// UI
	m_texturePathMap[TextureID::button] = "asset/image/craftpix/button.png";
	m_texturePathMap[TextureID::list] = "asset/image/craftpix/list.png";
	m_texturePathMap[TextureID::blank] = "asset/image/blank.PNG";
	// Shinobi
	m_texturePathMap[TextureID::Shinobi_Attack_1] = "asset/image/Shinobi/Attack_1.png";
	m_texturePathMap[TextureID::Shinobi_Attack_2] = "asset/image/Shinobi/Attack_2.png";
	m_texturePathMap[TextureID::Shinobi_Attack_3] = "asset/image/Shinobi/Attack_3.png";
	m_texturePathMap[TextureID::Shinobi_Dead] = "asset/image/Shinobi/Dead.png";
	m_texturePathMap[TextureID::Shinobi_Hurt] = "asset/image/Shinobi/Hurt.png";
	m_texturePathMap[TextureID::Shinobi_Idle] = "asset/image/Shinobi/Idle.png";
	m_texturePathMap[TextureID::Shinobi_Jump] = "asset/image/Shinobi/Jump.png";
	m_texturePathMap[TextureID::Shinobi_Run] = "asset/image/Shinobi/Run.png";
	m_texturePathMap[TextureID::Shinobi_Shield] = "asset/image/Shinobi/Shield.png";
	m_texturePathMap[TextureID::Shinobi_Walk] = "asset/image/Shinobi/Walk.png";

}
