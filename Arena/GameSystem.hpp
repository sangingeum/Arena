#pragma once
#include <entt.hpp>
#include "Component.hpp"
#include "Config.hpp"
#include <vector>
#include <memory>
#include <map>
#include "Scene.hpp"
#include "SceneMenu.hpp"
#include "SceneLoader.hpp"
#include "ActionBinder.hpp"

class GameSystem
{
	using SceneMap = std::map<SceneID, std::shared_ptr<Scene>>;
private:
	Config& m_config;
	sf::RenderWindow m_window;
	SceneMap m_sceneMap;
	SceneID m_currentSceneID{ SceneID::mainMenu };

public:
	GameSystem()
		: m_config(Config::instance()), m_window(sf::VideoMode(m_config.windowWidth, m_config.widowHeight), m_config.windowName)
	{
		init();
	}
	~GameSystem() = default;
	void run() {
		while (m_window.isOpen()) {
			sUpdate();
			sPhysics();
			sHandleInput();
			sRender();
		}
	}
	void quit() {
		m_window.close();
	}

private:
	void init() {
		m_window.setFramerateLimit(m_config.frameRate);
		float winHalfWidth = m_config.windowWidth / 2.f;
		float winHalfHeight = m_config.widowHeight / 2.f;
		auto curView = m_window.getView();
		curView.setCenter({ winHalfWidth * m_config.screenToWorldRatio, winHalfHeight * m_config.screenToWorldRatio });
		curView.zoom(m_config.screenToWorldRatio);
		m_window.setView(curView);
		changeScene(SceneID::mainMenu, false, true);
	}
	inline std::shared_ptr<Scene> getCurrentScene() {
		return m_sceneMap[m_currentSceneID];
	}
	void changeScene(SceneID id, bool destroyCurrentScene, bool overwriteIfExists) {
		if (m_sceneMap.find(id) == m_sceneMap.end() || overwriteIfExists)
			m_sceneMap[id] = SceneLoader::createScene(id);
		if (destroyCurrentScene)
			m_sceneMap.erase(m_currentSceneID);
		m_currentSceneID = id;
	}

	// Game loop functions
	void sUpdate() {
		getCurrentScene()->sUpdate();
	}
	void sHandleInput() {
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			Action action = ActionBinder::getAction(event);
			getCurrentScene()->sHandleAction(std::move(action));
		}
	}
	void sPhysics() {
		getCurrentScene()->sPhysics();
	}
	void sRender() {
		m_window.clear();
		getCurrentScene()->sRender(m_window);
		m_window.display();
	}

};

