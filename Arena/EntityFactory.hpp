#pragma once
#include "Component.hpp"
#include <box2d/box2d.h>
#include <entt.hpp>
#include "AssetManager.hpp"

class EntityFactory
{
public:
	static entt::entity createPhysicalBox(entt::registry& registry, b2World& world, float halfWidth, float halfHeight, float xPos, float yPos, b2BodyType type = b2BodyType::b2_dynamicBody, float xVel = 0.f, float yVel = 0.f) {
		auto entity = registry.create();
		registry.emplace<CCollision>(entity, world, entity, halfWidth, halfHeight, xPos, yPos, type, xVel, yVel);
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
	static entt::entity createShinobi(entt::registry& registry, b2World& world, float halfWidth, float halfHeight, float xPos, float yPos) {
		auto entity = registry.create();
		auto& cAnimation = registry.emplace<CAnimation>(entity, AssetManager::getTexture(TextureID::Shinobi_Idle), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 6, 3.f, sf::Vector2f{ 0.f, -halfHeight * 0.35f });
		registry.emplace<CCollision>(entity, world, entity, halfWidth * 0.35f, halfHeight * 0.6f, xPos, yPos);
		return entity;
	}
};

