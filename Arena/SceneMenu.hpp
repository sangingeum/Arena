#pragma once
#include "Scene.hpp"
#include "BaseGameSystem.hpp"
#include "Component.hpp"
#include "Config.hpp"
#include "ContactListener.hpp"

class SceneMenu : public Scene
{
	entt::registry m_registry{};
	BaseGameSystem& m_gameSystem;
	Config& m_config;
	const b2Vec2 m_gravity{ 0, 9.8f };
	b2World m_world{ m_gravity };
	myContactListener m_listener{ m_registry };
	int32 velocityIterations;
	int32 positionIterations;
public:
	SceneMenu(BaseGameSystem& gameSystem)
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
		m_registry.view<CPhysics, CRenderable>().each([&](const entt::entity entiy, CPhysics& cPhysics, CRenderable& CRender) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(CRender.shape, t);
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
			window.close();
			break;
		case ActionID::mousePrimary: {
			auto [flag, x, y] = action.args;
			if (flag) {
				float ratio = m_config.screenToWorldRatio;
				auto worldPos = window.mapPixelToCoords({ static_cast<int>(x), static_cast<int>(y) });
				auto entity = m_registry.create();
				m_registry.emplace<CPhysics>(entity, m_world, entity, 30 * ratio, 30 * ratio, worldPos.x, worldPos.y);
				m_registry.emplace<CRenderable>(entity, 30 * ratio, 30 * ratio);
			}
			break;
		}
		case ActionID::number2: {
			m_gameSystem.changeScene(SceneID::play, true, true);
			break;
		}
		default:
			break;
		}

	}
private:
	void init() {
		float winHalfWidth = m_config.halfWindowWidth;
		float winHalfHeight = m_config.halfWindowHeight;
		float ratio = m_config.screenToWorldRatio;
		auto entity = m_registry.create();
		m_registry.emplace<CPhysics>(entity, m_world, entity, winHalfWidth * ratio, 1 * ratio, winHalfWidth * ratio, 0, b2BodyType::b2_staticBody);
		m_registry.emplace<CRenderable>(entity, winHalfWidth * ratio, 1 * ratio);

		entity = m_registry.create();
		m_registry.emplace<CPhysics>(entity, m_world, entity, winHalfWidth * ratio, 1 * ratio, winHalfWidth * ratio, winHalfHeight * 2.f * ratio, b2BodyType::b2_staticBody);
		m_registry.emplace<CRenderable>(entity, winHalfWidth * ratio, 1 * ratio);
		entity = m_registry.create();
		m_registry.emplace<CPhysics>(entity, m_world, entity, 1 * ratio, winHalfHeight * ratio, 0, winHalfHeight * ratio, b2BodyType::b2_staticBody);
		m_registry.emplace<CRenderable>(entity, 1 * ratio, winHalfHeight * ratio);
		entity = m_registry.create();
		m_registry.emplace<CPhysics>(entity, m_world, entity, 1 * ratio, winHalfHeight * ratio, winHalfWidth * 2.f * ratio, winHalfHeight * ratio, b2BodyType::b2_staticBody);
		m_registry.emplace<CRenderable>(entity, 1 * ratio, winHalfHeight * ratio);
		for (int i = 0; i < 10; ++i) {
			auto entity = m_registry.create();
			m_registry.emplace<CPhysics>(entity, m_world, entity, 10 * ratio, 10 * ratio, (100 + i * 70.f) * ratio, 200.f * ratio, b2BodyType::b2_dynamicBody);
			m_registry.emplace<CRenderable>(entity, 10 * ratio, 10 * ratio);
			entity = m_registry.create();
			m_registry.emplace<CPhysics>(entity, m_world, entity, 10 * ratio, 10 * ratio, (100 + i * 70.f) * ratio, 300.f * ratio, b2BodyType::b2_dynamicBody);
			m_registry.emplace<CRenderable>(entity, 10 * ratio, 10 * ratio);
		}
	}

};

