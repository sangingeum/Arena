#pragma once
#include "Scene.hpp"
#include "BaseGameSystem.hpp"
#include "Component.hpp"
#include "Config.hpp"
#include "EntityCreator.hpp"

class SceneMenu : public Scene
{
	entt::registry m_registry{};
	BaseGameSystem& m_gameSystem;
	Config& m_config;
public:
	SceneMenu(BaseGameSystem& gameSystem)
		: m_gameSystem(gameSystem),
		m_config(Config::instance())
	{
		init();
	}

	void sRender(sf::RenderWindow& window) override {
		float radianToDegree = m_config.radianToDegree;
		m_registry.view<CText, CTransform>().each([&](const entt::entity entiy, CText& cText, CTransform& cTransform) {
			window.draw(cText.text, cTransform.transform);
			});
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
		case ActionID::number2: {
			m_gameSystem.changeScene(SceneID::play, true, true);
			break;
		}
		case ActionID::characterMoveUp: {
			m_registry.view<CText, CTransform>().each([](const entt::entity entiy, CText& cText, CTransform& cTransform) {
				cText.text.setFillColor(sf::Color::Green);
				});
			break;
		}
		case ActionID::characterMoveDown: {
			m_registry.view<CText, CTransform>().each([](const entt::entity entiy, CText& cText, CTransform& cTransform) {
				cText.text.setFillColor(sf::Color::White);
				});
			break;
		}
		default:
			break;
		}

	}
private:
	void init() {
		EntityCreator::createText(m_registry, "Hi!!");
	}

};

