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
	const b2Vec2 m_gravity{ 0, 20.0f };
	b2World m_world{ m_gravity };
	ContactListenerPlayScene m_listener{ m_registry };
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
		m_registry.view<CCollision, CRenderable>().each([&](const entt::entity entity, CCollision& cPhysics, CRenderable& cRender) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cRender.shape, t);
			});
		m_registry.view<CCollision, CAnimation, CPlayerContext>().each([&](const entt::entity entity, CCollision& cPhysics, CAnimation& cAnimation, CPlayerContext& CPlayerContext) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cAnimation.sprite, t * CPlayerContext.getDirection());
			});
	}
	void sUpdate() override {
		m_registry.view<CPlayerContext, CCollision>().each([&](const entt::entity entity, CPlayerContext& cPlayerContext, CCollision& cCollision) {
			// Update state
			cPlayerContext.update();
			// Update player velocity
			cCollision.body->SetLinearVelocity(cPlayerContext.calculateNextVelocity(cCollision.body->GetLinearVelocity()));
			});
		// Change state animation if necessary
		m_registry.view<CPlayerContext, CAnimation>().each([&](const entt::entity entity, CPlayerContext& CPlayerContext, CAnimation& cAnimation) {
			if (CPlayerContext.retrieveAndResetNeedAnimationUpdate()) {
				m_registry.emplace_or_replace<CAnimation>(entity, CPlayerContext.getAnimation());
			}
			});

	}
	void sAnimation(float timeStep) override {
		m_registry.view<CAnimation>().each([timeStep](const entt::entity entiy, CAnimation& cAnimation) {
			cAnimation.updateFrame(timeStep);
			});
	}
	void sCooldown(float timeStep) override {
		m_registry.view<CPlayerContext, CCollision>().each([&](const entt::entity entiy, CPlayerContext& CPlayerContext, CCollision& cCollision) {
			CPlayerContext.UpJumpCooldown = std::max(0.f, CPlayerContext.UpJumpCooldown - timeStep);
			CPlayerContext.DownJumpCooldown = std::max(0.f, CPlayerContext.DownJumpCooldown - timeStep);
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
		case ActionID::characterJump:
		case ActionID::leftShift:
		case ActionID::characterAttack1:
		case ActionID::characterAttack2:
		case ActionID::characterAttack3:
		{
			auto [pressed, x, y] = action.args;
			m_registry.view<CPlayerContext>().each([&](const entt::entity entiy, CPlayerContext& CPlayerContext) {
				CPlayerContext.handleAction(action.id, pressed);
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
				auto worldPos = window.mapPixelToCoords({ static_cast<int>(x), static_cast<int>(y) });
				EntityFactory::createPhysicalBox(m_registry, m_world, 0.5f, 0.5f, worldPos.x, worldPos.y);
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
			auto [pressed, x, y] = action.args;
			if (pressed) {
				if (m_gameSystem.getPaused())
					m_gameSystem.unpause();
				else
					m_gameSystem.pause();
			}
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
		// Boundary boxes
		EntityFactory::createPhysicalBox(m_registry, m_world, 5000.f, 0.1f, 0, 0, b2BodyType::b2_staticBody);
		EntityFactory::createShinobi(m_registry, m_world, 0.f, -2.f);
	}

};

