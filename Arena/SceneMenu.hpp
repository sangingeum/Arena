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
	Config& m_config;
	UIGraph m_uigraph;

public:
	SceneMenu(BaseGameSystem& gameSystem)
		: m_gameSystem(gameSystem),
		m_config(Config::instance()),
		m_uigraph(m_config.windowWidth, m_config.widowHeight)
	{
		init();
	}

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
		//EntityCreator::createText(m_registry, "Hi!!");
		auto root = std::make_unique<UIInternalNode>();
		auto node = std::make_unique<UIInternalNode>();
		for (int i = 1; i <= 5; ++i) {
			for (int j = 1; j <= 5; ++j) {
				node->addChildren(std::make_unique<UILeaf>(sf::Transform(1, 0, i * 100, 0, 1, j * 100, 0, 0, 1)));
			}
		}
		//node->addChildren(std::make_unique<UILeaf>(sf::Transform(1, 0, 50, 0, 1, 50, 0, 0, 1)));

		root->addChildren(std::move(node));
		m_uigraph.addChildren(std::move(root));
	}

};

