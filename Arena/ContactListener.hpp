#pragma once
#include <box2d/box2d.h>
#include <entt.hpp>
#include "Component.hpp"

class ContactListenerWhiteGreen : public b2ContactListener {
	entt::registry& m_registry;
public:
	ContactListenerWhiteGreen(entt::registry& registry)
		: m_registry(registry)
	{}

	void BeginContact(b2Contact* contact) override {
		for (auto* fixture : { contact->GetFixtureA() , contact->GetFixtureB() }) {
			entt::entity entity = (entt::entity)fixture->GetBody()->GetUserData().pointer;
			auto& cPhysics = m_registry.get<CPhysics>(entity);
			auto& cRenderable = m_registry.get<CRenderable>(entity);
			++cPhysics.numContacts;
			cRenderable.shape.setFillColor(sf::Color::Green);
		}
	}

	void EndContact(b2Contact* contact) override {
		for (auto* fixture : { contact->GetFixtureA() , contact->GetFixtureB() }) {
			entt::entity entity = (entt::entity)fixture->GetBody()->GetUserData().pointer;
			auto& cPhysics = m_registry.get<CPhysics>(entity);
			auto& cRenderable = m_registry.get<CRenderable>(entity);
			--cPhysics.numContacts;
			if (!cPhysics.numContacts)
				cRenderable.shape.setFillColor(sf::Color::White);
		}
	}
};
