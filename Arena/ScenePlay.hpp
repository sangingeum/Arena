#pragma once
#include "Scene.hpp"
#include "BaseGameSystem.hpp"
#include "Component.hpp"
#include "Config.hpp"
#include "ContactListener.hpp"
#include "EntityCreator.hpp"

class ScenePlay : public Scene
{
	entt::registry m_registry{};
	BaseGameSystem& m_gameSystem;
	Config& m_config;
	const b2Vec2 m_gravity{ 0, 9.8f };
	b2World m_world{ m_gravity };
	ContactListenerWhiteGreen m_listener{ m_registry };
	int32 velocityIterations;
	int32 positionIterations;
public:
	ScenePlay(BaseGameSystem& gameSystem)
		: m_gameSystem(gameSystem),
		m_config(Config::instance()),
		velocityIterations(m_config.velocityIterations),
		positionIterations(m_config.positionIterations)
	{
		m_world.SetContactListener(&m_listener);
		init();
	}

	void sRender(sf::RenderWindow& window) override {
		float radianToDegree = m_config.radianToDegree;
		m_registry.view<CPhysics, CRenderable>().each([&](const entt::entity entiy, CPhysics& cPhysics, CRenderable& cRender) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cRender.shape, t);
			});
	}
	void sUpdate() override {

	}
	void sPhysics(float timeStep) override {
		m_world.Step(timeStep, velocityIterations, positionIterations);
	}
	void sHandleAction(sf::RenderWindow& window, Action action) override {
		switch (action.id)
		{
		case ActionID::cameraZoom:
		{
			auto [flag, zoom, y] = action.args;
			auto curView = window.getView();
			curView.zoom(zoom);
			window.setView(curView);
			break;
		}
		case ActionID::windowClose:
			m_gameSystem.quit();
			break;
		case ActionID::mousePrimary: {
			auto [flag, x, y] = action.args;
			if (flag) {
				float ratio = 0.01f;
				auto worldPos = window.mapPixelToCoords({ static_cast<int>(x), static_cast<int>(y) });
				auto entity = m_registry.create();
				m_registry.emplace<CPhysics>(entity, m_world, entity, 30 * ratio, 30 * ratio, worldPos.x, worldPos.y);
				m_registry.emplace<CRenderable>(entity, 30 * ratio, 30 * ratio);
			}
			break;
		}
		case ActionID::number1: {
			m_gameSystem.changeScene(SceneID::mainMenu, true, true);
			break;
		}
		case ActionID::number2: {
			m_gameSystem.unpause();
			break;
		}
		case ActionID::number3: {
			m_gameSystem.pause();
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
	void changeResolution(unsigned width, unsigned height) override {

	}
	void adjustView(sf::RenderWindow& window) override {
		window.setView(sf::View{ sf::FloatRect{0.f, 0.f, 12.8f, 7.2f} });
	}
private:
	void init() {
		float winHalfWidth = 640;
		float winHalfHeight = 360;
		float ratio = 0.01f;
		//Boundary boxes
		EntityCreator::createPhysicalBox(m_registry, m_world, winHalfWidth * ratio, 1 * ratio, winHalfWidth * ratio, 0, b2BodyType::b2_staticBody);
		EntityCreator::createPhysicalBox(m_registry, m_world, winHalfWidth * ratio, 1 * ratio, winHalfWidth * ratio, winHalfHeight * 2.f * ratio, b2BodyType::b2_staticBody);
		EntityCreator::createPhysicalBox(m_registry, m_world, 1 * ratio, winHalfHeight * ratio, 0, winHalfHeight * ratio, b2BodyType::b2_staticBody);
		EntityCreator::createPhysicalBox(m_registry, m_world, 1 * ratio, winHalfHeight * ratio, winHalfWidth * 2.f * ratio, winHalfHeight * ratio, b2BodyType::b2_staticBody);
	}

};

