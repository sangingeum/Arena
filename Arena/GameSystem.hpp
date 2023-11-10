#pragma once
#include <unordered_map>
#include <memory>
#include "BaseGameSystem.hpp"
#include "SceneLoader.hpp"
#include "ActionBinder.hpp"
#include "Config.hpp"
#include <mutex>
#include <iostream>

class GameSystem : public BaseGameSystem
{
	using SceneMap = std::unordered_map<SceneID, std::shared_ptr<Scene>>;
private:
	Config& m_config;
	sf::RenderWindow m_window;
	SceneMap m_sceneMap;
	SceneID m_currentSceneID{ SceneID::mainMenu };
	bool m_pause{ false };
public:
	GameSystem()
		: m_config(Config::instance()), m_window(sf::VideoMode(m_config.windowWidth, m_config.widowHeight), m_config.windowName, sf::Style::Titlebar | sf::Style::Close)
	{
		init();
	}
	~GameSystem() = default;
	void run() override {
		sf::Clock clock;
		while (m_window.isOpen()) {
			float timeStep = clock.restart().asSeconds();
			if (!m_pause) {
				sUpdate();
				sPhysics(timeStep);
			}
			sHandleInput();
			sRender();
		}
	}
	void quit() override {
		m_window.close();
	}
	void pause() override {
		m_pause = true;
	}
	void unpause() override {
		m_pause = false;
	}
	void changeScene(SceneID id, bool destroyCurrentScene, bool overwriteIfExists) override {
		if (destroyCurrentScene)
			m_sceneMap.erase(m_currentSceneID);
		if (m_sceneMap.find(id) == m_sceneMap.end() || overwriteIfExists)
			m_sceneMap[id] = SceneLoader::createScene(id, *this);
		m_sceneMap[id]->adjustView(m_window);
		m_currentSceneID = id;
	}

	void changeResolution(unsigned width = 1280, unsigned height = 720) override {
		m_config.changeResolution(width, height);
		m_window.setSize({ width, height });
		//m_window.create(sf::VideoMode(m_config.windowWidth, m_config.widowHeight), m_config.windowName, sf::Style::Fullscreen);
		for (auto& [id, scene] : m_sceneMap) {
			scene->changeResolution(width, height);
		}
		getCurrentScene()->adjustView(m_window);
	}

private:
	void init() {
		m_window.setVerticalSyncEnabled(true);
		m_window.setFramerateLimit(m_config.frameRate);
		changeScene(SceneID::mainMenu, false, true);
	}
	inline std::shared_ptr<Scene> getCurrentScene() {
		return m_sceneMap[m_currentSceneID];
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
			getCurrentScene()->sHandleAction(m_window, std::move(action));
		}
	}
	void sPhysics(float timeStep) {
		getCurrentScene()->sPhysics(timeStep);
	}
	void sRender() {
		m_window.clear();
		getCurrentScene()->sRender(m_window);
		m_window.display();
	}

};

