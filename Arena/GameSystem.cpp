#include "GameSystem.hpp"

GameSystem::GameSystem()
	: m_config(Config::instance()), m_window(sf::VideoMode(m_config.windowWidth, m_config.windowHeight), m_config.windowName, sf::Style::Titlebar | sf::Style::Close)
{
	init();
}

void GameSystem::run() {
	sf::Clock clock;
	while (m_window.isOpen()) {
		float timeStep = clock.restart().asSeconds();
		sHandleInput();
		if (!m_pause) {
			sCooldown(timeStep);
			sUpdate();
			sPhysics(timeStep);
			sAnimation(timeStep);
		}
		sRender();
	}
}

void GameSystem::quit() {
	if (m_window.isOpen()) {
		m_window.close();
	};
}

void GameSystem::pause() {
	m_pause = true;
}

void GameSystem::unpause() {
	m_pause = false;
}

bool GameSystem::getPaused()
{
	return m_pause;
}

void GameSystem::changeScene(SceneID id, bool destroyCurrentScene, bool overwriteIfExists) {
	if (destroyCurrentScene)
		m_sceneMap.erase(m_currentSceneID);
	if (m_sceneMap.find(id) == m_sceneMap.end() || overwriteIfExists)
		m_sceneMap[id] = SceneLoader::createScene(id, *this);
	m_sceneMap[id]->adjustView(m_window);
	m_currentSceneID = id;
}

void GameSystem::changeResolution(unsigned width, unsigned height) {
	m_config.changeResolution(width, height);
	m_window.setSize({ width, height });
	//m_window.create(sf::VideoMode(m_config.windowWidth, m_config.widowHeight), m_config.windowName, sf::Style::Fullscreen);
	for (auto& [id, scene] : m_sceneMap) {
		scene->changeResolution(width, height);
	}
	getCurrentScene()->adjustView(m_window);
}


// Game loop functions

void GameSystem::init() {
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(m_config.frameRate);
	changeScene(SceneID::mainMenu, false, true);
}

void GameSystem::sAnimation(float timeStep)
{
	static float accumulatedTime{ 0.f };
	accumulatedTime += timeStep;
	float deltaTime = m_config.deltaTime;
	while (accumulatedTime > deltaTime) {
		accumulatedTime -= deltaTime;
		getCurrentScene()->sAnimation(deltaTime);
	}
}

void GameSystem::sUpdate() {
	getCurrentScene()->sUpdate();
}

void GameSystem::sHandleInput() {
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		Action action = ActionBinder::getAction(event);
		getCurrentScene()->sHandleAction(m_window, std::move(action));
	}
}

void GameSystem::sCooldown(float timeStep)
{
	static float accumulatedTime{ 0.f };
	accumulatedTime += timeStep;
	float deltaTime = m_config.deltaTime;
	while (accumulatedTime > deltaTime) {
		accumulatedTime -= deltaTime;
		getCurrentScene()->sCooldown(deltaTime);
	}
}

void GameSystem::sPhysics(float timeStep) {
	static float accumulatedTime{ 0.f };
	accumulatedTime += timeStep;
	float deltaTime = m_config.deltaTime;
	while (accumulatedTime > deltaTime) {
		accumulatedTime -= deltaTime;
		getCurrentScene()->sPhysics(deltaTime);
	}
}

void GameSystem::sRender() {
	m_window.clear();
	getCurrentScene()->sRender(m_window);
	m_window.display();
}
