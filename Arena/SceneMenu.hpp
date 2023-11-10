#pragma once
#include "Scene.hpp"
#include "BaseGameSystem.hpp"
#include "Component.hpp"
#include "Config.hpp"
#include "EntityCreator.hpp"
#include "UIGraph.hpp"

class SceneMenu : public Scene
{
	entt::registry m_registry{};
	BaseGameSystem& m_gameSystem;
	Config& m_config{ Config::instance() };
	UIGraph m_uigraph{};

public:
	SceneMenu(BaseGameSystem& gameSystem)
		: m_gameSystem(gameSystem)
	{
		init();
	}
	~SceneMenu() = default;
	void sRender(sf::RenderWindow& window) override {
		float radianToDegree = m_config.radianToDegree;
		m_registry.view<CText, CTransform>().each([&](const entt::entity entiy, CText& cText, CTransform& cTransform) {
			window.draw(cText.text, cTransform.transform);
			});
		if (!m_uigraph.getHidden())
			m_uigraph.render(window);
	}
	void sUpdate() override {
	}
	void sPhysics(float timeStep) override {
	}
	void sHandleAction(sf::RenderWindow& window, Action action) override {
		switch (action.id)
		{
		case ActionID::windowClose:
			m_gameSystem.quit();
			break;
		case ActionID::cameraZoom:
		{
			auto [flag, zoom, y] = action.args;
			auto curView = window.getView();
			curView.zoom(zoom);
			window.setView(curView);
			break;
		}
		case ActionID::mousePrimary:
			// UI click
			m_uigraph.mouseClick(std::move(action.args));
			// Screen click
			break;
		case ActionID::mouseMove:
			m_uigraph.mouseMove(std::move(action.args));
			break;
		case ActionID::number2: {
			m_gameSystem.changeScene(SceneID::play, true, true);
			break;
		}
		case ActionID::characterMoveUp: {
			m_uigraph.setHidden(false);
			break;
		}
		case ActionID::characterMoveDown: {
			m_uigraph.setHidden(true);
			break;
		}
		case ActionID::number4: {
			m_gameSystem.changeResolution(1280, 720);
			break;
		}
		case ActionID::number5: {
			m_gameSystem.changeResolution(1920, 1080);
			break;
		}
		default:
			break;
		}

	}

	// It will be called by the game system
	void changeResolution(unsigned width, unsigned height) override {
		m_uigraph.changeResolution(width, height);
	}
	void adjustView(sf::RenderWindow& window) override {
		window.setView(sf::View{ sf::FloatRect{0.f, 0.f, 12.8f, 7.2f} });
	}
private:
	void init() {
		auto mainBar = std::make_unique<UIInternalNode>();
		for (int i = 0; i < 5; ++i) {
			auto nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 50.f + i * 100.f, 0, 1, 50.f, 0, 0, 1));
			nodePtr->getRect().setSize({ 50.f, 50.f });
			nodePtr->getRect().setFillColor(sf::Color::White);
			mainBar->addChild(std::move(nodePtr));
		}
		mainBar->getRect().setFillColor(sf::Color{ 100, 100, 100, 100 });
		mainBar->getRect().setSize({ 550, 150 });
		mainBar->setAnchor(0.5f, 0.9f);
		mainBar->setAnchorType(UIAnchorType::midBottom);
		//
		auto sideBar = std::make_unique<UIInternalNode>();
		for (int i = 0; i < 7; ++i) {
			auto nodePtr = std::make_unique<UILeaf>(sf::Transform(1, 0, 50.f, 0, 1, 50.f + i * 100.f, 0, 0, 1));
			nodePtr->getRect().setSize({ 50.f, 50.f });
			nodePtr->getRect().setFillColor(sf::Color::White);
			sideBar->addChild(std::move(nodePtr));
		}
		sideBar->getRect().setFillColor(sf::Color{ 100, 100, 100, 100 });
		sideBar->getRect().setSize({ 150, 750 });
		sideBar->setAnchor(0.1f, 0.5f);
		sideBar->setAnchorType(UIAnchorType::leftMid);
		//
		m_uigraph.addChild(std::move(mainBar));
		m_uigraph.addChild(std::move(sideBar));
		m_uigraph.changeResolution(m_config.windowWidth, m_config.widowHeight);

	}

};

