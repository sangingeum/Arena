#pragma once
#include "UIRoot.hpp"
#include "AssetManager.hpp"
#include "BaseGameSystem.hpp"

class UIFactory
{
public:
	static std::unique_ptr<UIInternalNode> createMainMenu(BaseGameSystem& gameSystem) {
		auto menu = std::make_unique<UIInternalNode>();
		menu->getSprite().setTexture(AssetManager::getTexture(TextureID::list));
		menu->getSprite().setTextureRect({ 0, 0, 111, 231 });
		menu->getSprite().setScale(3.f, 2.f);
		menu->setAnchor(0.5f, 0.9f);
		menu->setAnchorType(UIAnchorType::midBottom);
		for (int i = 0; i < 3; ++i) {
			auto nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 66.5f, 0, 1, 100.f + 100.f * i, 0, 0, 1));
			nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
			nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
			nodePtr->setOnClickHandler([&]() {gameSystem.changeScene(SceneID::play, true, true); });
			menu->addChildBack(std::move(nodePtr));
		}
		return std::move(menu);
	}

	static std::unique_ptr<UIInternalNode> createSettingMenu(BaseGameSystem& gameSystem) {
		auto menu = std::make_unique<UIInternalNode>();
		menu->getSprite().setTexture(AssetManager::getTexture(TextureID::list));
		menu->getSprite().setTextureRect({ 0, 0, 111, 231 });
		menu->getSprite().setScale(5.f, 2.f);
		menu->setAnchor(0.5f, 0.5f);
		menu->setAnchorType(UIAnchorType::center);
		for (int i = 0; i < 3; ++i) {
			auto nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 66.5f, 0, 1, 100.f + 100.f * i, 0, 0, 1));
			nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
			nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
			nodePtr->setOnClickHandler([&]() {gameSystem.changeScene(SceneID::play, true, true); });
			menu->addChildBack(std::move(nodePtr));
		}
		return std::move(menu);
	}

};

