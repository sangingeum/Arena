#pragma once
#include "SceneLoader.hpp"
#include "ActionBinder.hpp"

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
	GameSystem();
	~GameSystem() = default;
	void run() override;
	void quit() override;
	void pause() override;
	void unpause() override;
	bool getPaused() override;
	void changeScene(SceneID id, bool destroyCurrentScene, bool overwriteIfExists) override;
	void changeResolution(unsigned width = 1280, unsigned height = 720) override;
private:
	void init();
	inline std::shared_ptr<Scene> getCurrentScene();
	// Game loop functions
	void sUpdate();
	void sAnimation(float timeStep);
	void sHandleInput();
	void sCooldown(float timeStep);
	void sPhysics(float timeStep);
	void sRender();

};


// inline functions
std::shared_ptr<Scene> GameSystem::getCurrentScene() {
	return m_sceneMap[m_currentSceneID];
}