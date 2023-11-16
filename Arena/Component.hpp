#pragma once
#include "Config.hpp"
#include <box2d/box2d.h>
#include <entt.hpp>
#include <SFML/Graphics.hpp>
#include "State.hpp"

struct CTransform
{
	sf::Transform transform;
	CTransform()
		: transform{ sf::Transform::Identity }
	{}
};

struct CText
{
	sf::Text text;
	CText(const sf::String& string) {
		text.setFont(Config::instance().font);
		text.setString(string);
		text.setFillColor(sf::Color::White);
		adjustCenter();
		text.setCharacterSize(24);
	}
	void adjustCenter() {
		auto bound = text.getLocalBounds();
		text.setOrigin({ bound.width / 2.f, bound.height / 2.f });
	}
};

struct CRenderable
{
	sf::RectangleShape shape;
	CRenderable(float halfWidth, float halfHeight)
		: shape({ 2.f * halfWidth, 2.f * halfHeight })
	{
		shape.setOrigin({ halfWidth, halfHeight });
		shape.setPosition({ 0, 0 });
	}
};

struct CSprite {
	sf::Sprite sprite;
	CSprite(sf::Texture& texture, sf::IntRect rect)
		:sprite(texture, std::move(rect))
	{}
};

struct CAnimation {
	sf::Sprite sprite;
	uint32_t width;
	uint32_t height;
	uint32_t frameCount;
	float timePerFrame;
	uint32_t curFrame{ 0 };
	float curFrameTime{ 0.f };
	CAnimation(sf::Texture& texture, sf::IntRect rect, sf::Vector2f targetWorldSize, uint32_t frameCount_, float animTime, sf::Vector2f positionOffset = { 0.f, 0.f })
		:sprite(texture, rect), width(rect.width), height(rect.height), frameCount(frameCount_), timePerFrame(animTime / frameCount_)
	{
		sprite.setOrigin(sprite.getLocalBounds().getSize() / 2.f);
		sprite.scale(targetWorldSize.x / width, targetWorldSize.y / height);
		sprite.move(positionOffset);
	}
	void updateFrame(float timeStep) {
		curFrameTime += std::min(timeStep, timePerFrame);
		if (curFrameTime > timePerFrame) {
			curFrame = ((curFrame + 1 == frameCount) ? 0 : curFrame + 1);
			curFrameTime -= timePerFrame;
			sprite.setTextureRect(sf::IntRect{ static_cast<int>(curFrame * width), 0, 128, 128 });
		}
	}

};

struct CCollision
{
	b2Body* body;
	uint32_t numContacts{ 0 };
	CCollision(b2World& world, entt::entity entity, float halfWidth, float halfHeight, float xPos, float yPos, b2BodyType type = b2BodyType::b2_dynamicBody, float xVel = 0.f, float yVel = 0.f,
		float friction = 0.4f, float restitution = 0.f, float density = 1.0f, bool fixedRotation = false)
	{
		b2BodyDef def;
		def.position.Set(xPos, yPos);
		def.type = type;
		def.fixedRotation = fixedRotation;
		body = world.CreateBody(&def);
		b2PolygonShape boxShape;
		boxShape.SetAsBox(halfWidth, halfHeight);
		b2FixtureDef fDef;
		fDef.shape = &boxShape;
		fDef.friction = friction;
		fDef.restitution = restitution;
		fDef.density = density;

		body->CreateFixture(&fDef);
		body->SetLinearVelocity({ xVel, yVel });
		body->GetUserData().pointer = (uintptr_t)entity;
	}
};

struct CState {
	StateID curID{ StateID::Idle };
	StateID nextID{ StateID::Idle };
};

struct CPlayerInput
{
	sf::Transform direction{ sf::Transform::Identity };
	bool moveUp{ false };
	bool moveDown{ false };
	bool moveLeft{ false };
	bool moveRight{ false };
	bool jump{ false };

	void handleAction(ActionID id, bool pressed) {
		switch (id)
		{
		case ActionID::characterMoveUp:
			moveUp = pressed;
			break;
		case ActionID::characterMoveLeft:
			moveLeft = pressed;
			if (pressed) {
				auto t = sf::Transform::Identity;
				direction = std::move(t.scale({ -1.f, 1.f }));
			}
			break;
		case ActionID::characterMoveDown:
			moveDown = pressed;
			break;
		case ActionID::characterMoveRight:
			moveRight = pressed;
			if (pressed) {
				direction = sf::Transform::Identity;
			}
			break;
		case ActionID::characterJump:
			jump = pressed;
			break;
		default:
			break;
		}
	}

	void reset() {
		moveUp = false;
		moveDown = false;
		moveLeft = false;
		moveRight = false;
		jump = false;
	}


};
