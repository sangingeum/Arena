#pragma once
#include "Config.hpp"
#include <box2d/box2d.h>
#include <entt.hpp>
#include <SFML/Graphics.hpp>

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

struct CPhysics
{
	b2Body* body;
	uint32_t numContacts{ 0 };
	CPhysics(b2World& world, entt::entity entity, float halfWidth, float halfHeight, float xPos, float yPos, b2BodyType type = b2BodyType::b2_dynamicBody, float xVel = 0.f, float yVel = 0.f)
	{
		b2BodyDef def;
		def.position.Set(xPos, yPos);
		def.type = type;
		body = world.CreateBody(&def);
		b2PolygonShape boxShape;
		boxShape.SetAsBox(halfWidth, halfHeight);
		b2FixtureDef fDef;
		fDef.shape = &boxShape;
		fDef.friction = 0.4f;
		fDef.density = 1.f;
		fDef.restitution = 0.3f;
		body->CreateFixture(&fDef);
		body->SetLinearVelocity({ xVel, yVel });
		body->GetUserData().pointer = (uintptr_t)entity;
	}
};

struct CPlayerInput
{
	//states

};