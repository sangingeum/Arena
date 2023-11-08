#pragma once
#include <entt.hpp>
#include <box2d/box2d.h>
#include "Component.hpp"

class EntityCreator
{
public:
	static entt::entity createPhysicalBox(entt::registry& registry, b2World& world, float halfWidth, float halfHeight, float xPos, float yPos, b2BodyType type = b2BodyType::b2_dynamicBody, float xVel = 0.f, float yVel = 0.f) {
		auto entity = registry.create();
		registry.emplace<CPhysics>(entity, world, entity, halfWidth, halfHeight, xPos, yPos, b2BodyType::b2_staticBody, xVel, yVel);
		registry.emplace<CRenderable>(entity, halfWidth, halfHeight);
		return entity;
	}
	static entt::entity createText(entt::registry& registry, const sf::String& string) {
		auto entity = registry.create();
		auto& cTransform = registry.emplace<CTransform>(entity);
		auto& cFont = registry.emplace<CText>(entity, string);
		cTransform.transform.translate({ 0.f, 0.f });
		cTransform.transform.scale({ 0.01f, 0.01f });
		return entity;
	}
};

