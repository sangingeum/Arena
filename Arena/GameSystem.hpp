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
		m_window.setFramerateLimit(m_config.frameRate);
		init();
	}
	~GameSystem() = default;
	void run() {
		while (m_window.isOpen()) {
			sUpdate();
			sHandleInput();
			sRender();
		}
	}
	void quit() {

	}

private:
	void init() {
		changeScene(SceneID::mainMenu, false, true);
	}
	std::shared_ptr<Scene> getCurrentScene() {
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

	}
	void sRender() {
		m_window.clear();


		m_window.display();
	}
};

