#pragma once
#include "ShinobiAnimation.hpp"
#include "CPlayerContext.hpp"
class EntityFactory
{
public:
	static entt::entity createPhysicalBox(entt::registry& registry, b2World& world, float halfWidth, float halfHeight, float xPos, float yPos, b2BodyType type = b2BodyType::b2_dynamicBody) {
		auto entity = registry.create();
		auto& cCollision = registry.emplace<CCollision>(entity, world, entity, xPos, yPos, type);
		cCollision.addBoxFixture(halfWidth, halfHeight);
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
	static entt::entity createShinobi(entt::registry& registry, b2World& world, float xPos, float yPos) {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		auto entity = registry.create();
		auto& anim = registry.emplace<CAnimation>(entity, ShinobiAnimation::getIdle());
		//anim.sprite.getTextureRect();
		auto& cCollision = registry.emplace<CCollision>(entity, world, entity, xPos, yPos, b2BodyType::b2_dynamicBody, true);
		cCollision.addBoxFixture(halfWidth * 0.25f, halfHeight * 0.6f, 0.f, halfHeight * 0.35f, 0.f, 0.7f, 0.f, 1.f, false); // hitbox
		auto* footFixture = cCollision.addBoxFixture(halfWidth * 0.20f, halfHeight * 0.05f, 0.f, halfHeight, 0.f, 0.0f, 0.f, 0.f, true); // foot sensor
		footFixture->GetUserData().pointer = 10000; // foot
		auto& cPlayerContext = registry.emplace<CPlayerContext>(entity);

		cPlayerContext.setDeadAnimationGetter([]() { return ShinobiAnimation::getDead(); });
		cPlayerContext.setHurtAnimationGetter([]() { return ShinobiAnimation::getHurt(); });
		cPlayerContext.setIdleAnimationGetter([]() { return ShinobiAnimation::getIdle(); });
		cPlayerContext.setJumpAnimationGetter([]() { return ShinobiAnimation::getJump(); });
		cPlayerContext.setRunAnimationGetter([]() { return ShinobiAnimation::getRun(); });
		cPlayerContext.setWalkAnimationGetter([]() { return ShinobiAnimation::getWalk(); });
		cPlayerContext.setAttackAnimationGetter([]() { return ShinobiAnimation::getAttack_1(); });

		return entity;
	}
};

