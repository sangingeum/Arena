#pragma once
#include "Component.hpp"
#include "UIFactory.hpp"


class SceneMenu : public Scene
{
	BaseGameSystem& m_gameSystem;
	entt::registry m_registry{};
	Config& m_config{ Config::instance() };
	UIRoot m_UIRoot{};
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
		if (!m_UIRoot.getHidden())
			m_UIRoot.render(window);
	}
	void sUpdate() override {
		m_UIRoot.update(m_config.windowWidth, m_config.windowHeight);
	}
	void sAnimation(float timeStep) override {

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
			m_UIRoot.mouseClick(std::move(action.args));
			// Screen click
			break;
		case ActionID::mouseMove:
			m_UIRoot.mouseMove(std::move(action.args));
			break;
		case ActionID::number2: {
			m_gameSystem.changeScene(SceneID::play, true, true);
			break;
		}
		case ActionID::characterMoveUp: {
			m_UIRoot.setHidden(false);
			break;
		}
		case ActionID::characterMoveDown: {
			m_UIRoot.setHidden(true);
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
		m_UIRoot.changeResolution(width, height);
	}
	void adjustView(sf::RenderWindow& window) override {
		window.setView(sf::View{ sf::FloatRect{0.f, 0.f, 12.8f, 7.2f} });
	}
private:
	void init() {
		m_UIRoot.addChildBack(UIFactory::createMainMenu(m_gameSystem, m_UIRoot));
		//m_UIRoot.addChildBack(UIFactory::createSettingMenu(m_gameSystem, m_UIRoot));
		m_UIRoot.changeResolution(m_config.windowWidth, m_config.windowHeight);
	}

};

