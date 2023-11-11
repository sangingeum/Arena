#pragma once
#include "UIRoot.hpp"
#include "UILeaf.hpp"
#include "AssetManager.hpp"
#include "BaseGameSystem.hpp"

class UIFactory
{
public:
	static std::unique_ptr<UIInternalNode> createMainMenu(BaseGameSystem& gameSystem, UIRoot& uiRoot) {
		auto menu = std::make_unique<UIInternalNode>();
		menu->getSprite().setTexture(AssetManager::getTexture(TextureID::list));
		menu->getSprite().setTextureRect({ 0, 0, 111, 231 });
		menu->getSprite().setScale(3.f, 2.f);
		menu->setAnchor(0.5f, 0.9f);
		menu->setAnchorType(UIAnchorType::midBottom);
		menu->setDraggable(false);
		// Start
		auto nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 66.5f, 0, 1, 100.f, 0, 0, 1));
		nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
		nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
		nodePtr->setOnClickHandler([&]() {gameSystem.changeScene(SceneID::play, true, true); });
		nodePtr->setAnchor(0.5f, 0.3f);
		nodePtr->setAnchorType(UIAnchorType::center);
		nodePtr->setText("Start");
		menu->addChildBack(std::move(nodePtr));
		// Setting
		nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 66.5f, 0, 1, 200.f, 0, 0, 1));
		nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
		nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
		nodePtr->setOnClickHandler([&]() { uiRoot.addLater(UIFactory::createSettingMenu(gameSystem, uiRoot)); });
		nodePtr->setAnchor(0.5f, 0.5f);
		nodePtr->setAnchorType(UIAnchorType::center);
		nodePtr->setText("Setting");
		menu->addChildBack(std::move(nodePtr));
		// Quit
		nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 66.5f, 0, 1, 300.f, 0, 0, 1));
		nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
		nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
		nodePtr->setOnClickHandler([&]() {gameSystem.quit(); });
		nodePtr->setAnchor(0.5f, 0.7f);
		nodePtr->setAnchorType(UIAnchorType::center);
		nodePtr->setText("Quit");
		menu->addChildBack(std::move(nodePtr));

		return std::move(menu);
	}

	static std::unique_ptr<UIInternalNode> createSettingMenu(BaseGameSystem& gameSystem, UIRoot& uiRoot) {

		auto background = std::make_unique<UIInternalNode>();
		background->getSprite().setTexture(AssetManager::getTexture(TextureID::blank));
		background->getSprite().setTextureRect({ 0, 0, 50, 50 });
		background->getSprite().setScale(100.f, 100.f);
		background->getSprite().setColor({ 0, 0, 0, 160 });
		background->setAnchor(0.5f, 0.5f);
		background->setAnchorType(UIAnchorType::center);

		auto menu = std::make_unique<UIInternalNode>();
		menu->getSprite().setTexture(AssetManager::getTexture(TextureID::list));
		menu->getSprite().setTextureRect({ 0, 0, 111, 231 });
		menu->getSprite().setScale(4.f, 2.f);
		menu->setAnchor(0.5f, 0.5f);
		menu->setAnchorType(UIAnchorType::center);

		// resolution
		auto nodePtr = std::make_unique<UILeaf>();
		nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
		nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
		nodePtr->setOnClickHandler([&]() { gameSystem.changeResolution(1920, 1080); });
		nodePtr->setAnchor(0.5f, 0.3f);
		nodePtr->setAnchorType(UIAnchorType::center);
		nodePtr->setText("1920x1080");
		menu->addChildBack(std::move(nodePtr));

		// resolution
		nodePtr = std::make_unique<UILeaf>();
		nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
		nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
		nodePtr->setOnClickHandler([&]() { gameSystem.changeResolution(1280, 720); });
		nodePtr->setAnchor(0.5f, 0.5f);
		nodePtr->setAnchorType(UIAnchorType::center);
		nodePtr->setText("1280x720");
		menu->addChildBack(std::move(nodePtr));

		// cancel
		nodePtr = std::make_unique<UILeaf>();
		nodePtr->getSprite().setTexture(AssetManager::getTexture(TextureID::button));
		nodePtr->getSprite().setTextureRect({ 0, 0, 200, 48 });
		nodePtr->setOnClickHandler([&, ptr = background.get()]() { uiRoot.popLater(ptr); });
		nodePtr->setAnchor(0.5f, 0.7f);
		nodePtr->setAnchorType(UIAnchorType::center);
		nodePtr->setText("Cancel");
		menu->addChildBack(std::move(nodePtr));

		background->addChildBack(std::move(menu));
		return std::move(background);
	}

};

