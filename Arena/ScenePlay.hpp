#pragma once
#include "BaseGameSystem.hpp"
#include "ContactListener.hpp"
#include "RayCastCallback.hpp"
#include "EntityFactory.hpp"
#include <iostream>
#include <limits>

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
		m_registry.view<CCollision, CRenderable>().each([&](const entt::entity entiy, CCollision& cPhysics, CRenderable& cRender) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cRender.shape, t);
			});
		m_registry.view<CCollision, CAnimation, CPlayerInput>().each([&](const entt::entity entiy, CCollision& cPhysics, CAnimation& cAnimation, CPlayerInput& cPlayerInput) {
			sf::Transform t;
			auto& pos = cPhysics.body->GetPosition();
			auto radian = cPhysics.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			window.draw(cAnimation.sprite, t * cPlayerInput.getDirection());
			});
	}
	void sUpdate() override {
		m_registry.view<CPlayerInput, CState, CCollision>().each([&](const entt::entity entiy, CPlayerInput& cPlayerInput, CState& cState, CCollision& cCollision) {
			// Set player velocity
			// Set x velocity
			b2Vec2 vel{ 0.f, cCollision.body->GetLinearVelocity().y };
			if (cPlayerInput.moveLeft)
				if (cPlayerInput.shift)
					vel.x = -cPlayerInput.runningSpeed;
				else
					vel.x = -cPlayerInput.walkingSpeed;
			if (cPlayerInput.moveRight)
				if (cPlayerInput.shift)
					vel.x = cPlayerInput.runningSpeed;
				else
					vel.x = cPlayerInput.walkingSpeed;
			// Set y velocity
			if (cPlayerInput.jump && (cPlayerInput.numObjectsOnFoot) && cPlayerInput.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
				cPlayerInput.resetUpJumpCooldown();
				vel.y = -cPlayerInput.upJumpSpeed;
			}
			else if (cPlayerInput.moveDown && (!cPlayerInput.numObjectsOnFoot) && cPlayerInput.DownJumpCooldown < std::numeric_limits<float>::epsilon()) {
				cPlayerInput.resetDownJumpCooldown();
				vel.y = cPlayerInput.downJumpSpeed;
			}
			cCollision.body->SetLinearVelocity(vel);
			// Change state
			if (cPlayerInput.numObjectsOnFoot)
				cState.nextID = StateID::Idle;
			else
				cState.nextID = StateID::Jump;

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
	void sCooldown(float timeStep) override {
		m_registry.view<CPlayerInput, CCollision>().each([&](const entt::entity entiy, CPlayerInput& cPlayerInput, CCollision& cCollision) {
			cPlayerInput.UpJumpCooldown = std::max(0.f, cPlayerInput.UpJumpCooldown - timeStep);
			cPlayerInput.DownJumpCooldown = std::max(0.f, cPlayerInput.DownJumpCooldown - timeStep);
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

