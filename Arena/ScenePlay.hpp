#pragma once
#include "BaseGameSystem.hpp"
#include "ContactListener.hpp"
#include "EntityFactory.hpp"
#include <iostream>

class ScenePlay : public Scene
{
	entt::registry m_registry{};
	BaseGameSystem& m_gameSystem;
	Config& m_config;
	const b2Vec2 m_gravity{ 0, 9.8f };
	b2World m_world{ m_gravity };
	//ContactListenerWhiteGreen m_listener{ m_registry };
	int32 velocityIterations;
	int32 positionIterations;
public:
	ScenePlay(BaseGameSystem& gameSystem)
		: m_gameSystem(gameSystem),
		m_config(Config::instance()),
		velocityIterations(m_config.velocityIterations),
		positionIterations(m_config.positionIterations)
	{
		//m_world.SetContactListener(&m_listener);
		init();
	}

	void sRender(sf::RenderWindow& window) override {
		float radianToDegree = m_config.radianToDegree;
		m_registry.view<CCollision, CRenderable>().each([&](const entt::entity entiy, CCollision& cPhysics, CRenderable& cRender) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cRender.shape, t);
			});
		m_registry.view<CCollision, CAnimation>().each([&](const entt::entity entiy, CCollision& cPhysics, CAnimation& cAnimation) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cAnimation.sprite, t);
			});
	}
	void sUpdate() override {

		m_registry.view<CPlayerInput, CState, CCollision>().each([](const entt::entity entiy, CPlayerInput& cPlayerInput, CState& cState, CCollision& cCollision) {
			// Set player velocity
			b2Vec2 vel{ 0, cCollision.body->GetLinearVelocity().y };
			if (cPlayerInput.moveLeft)
				vel.x = -4;
			if (cPlayerInput.moveRight)
				if (cPlayerInput.moveLeft)
					vel.x = 0;
				else
					vel.x = 4;
			if (cPlayerInput.jump) {
				vel.y = -5;
			}
			cCollision.body->SetLinearVelocity(vel);
			// Change state
			if (std::abs(vel.y) >= 0.1f) {
				cState.nextID = StateID::Jump;
			}
			else {
				cState.nextID = StateID::Idle;
			}
			});
		// Update state & Change state animation
		m_registry.view<CState, CAnimation>().each([&](const entt::entity entiy, CState& cState, CAnimation& cAnimation) {
			if (cState.curID != cState.nextID) {
				cState.curID = cState.nextID;
				switch (cState.curID)
				{
				case StateID::Idle:
					m_registry.replace<CAnimation>(entiy, ShinobiAnimation::getIdle());
					break;
				case StateID::Jump:
					m_registry.replace<CAnimation>(entiy, ShinobiAnimation::getJump());
					break;
				default:
					break;
				}
			}
			});


	}
	void sAnimation(float timeStep) override {
		m_registry.view<CAnimation>().each([timeStep](const entt::entity entiy, CAnimation& cAnimation) {
			cAnimation.updateFrame(timeStep);
			});
	}
	void sPhysics(float timeStep) override {
		m_world.Step(timeStep, velocityIterations, positionIterations);
	}
	void sHandleAction(sf::RenderWindow& window, Action action) override {
		switch (action.id)
		{
		case ActionID::characterMoveUp:
		case ActionID::characterMoveDown:
		case ActionID::characterMoveLeft:
		case ActionID::characterMoveRight:
		case ActionID::characterJump: {
			auto [pressed, x, y] = action.args;
			m_registry.view<CPlayerInput>().each([&](const entt::entity entiy, CPlayerInput& cPlayerInput) {
				cPlayerInput.handleAction(action.id, pressed);
				});
			break;
		}
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
				m_registry.emplace<CCollision>(entity, m_world, entity, 0.5f, 0.5f, worldPos.x, worldPos.y);
				m_registry.emplace<CRenderable>(entity, 0.5f, 0.5f);
				std::cout << worldPos.x << ", " << worldPos.y << "\n";
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
		case ActionID::pause: {
			if (m_gameSystem.getPaused())
				m_gameSystem.unpause();
			else
				m_gameSystem.pause();
			break;
		}
		default:
			break;
		}

	}
	void changeResolution(unsigned width, unsigned height) override {

	}
	void adjustView(sf::RenderWindow& window) override {
		window.setView(sf::View{ sf::FloatRect{-6.4f, -5.2f, 12.8f, 7.2f} });
	}
private:
	void init() {
		float ratio = 0.01f;
		// Boundary boxes
		EntityFactory::createPhysicalBox(m_registry, m_world, 5000.f, 0.1f, 0, 0, b2BodyType::b2_staticBody);
		EntityFactory::createShinobi(m_registry, m_world, 0.f, -2.f);
	}

};

