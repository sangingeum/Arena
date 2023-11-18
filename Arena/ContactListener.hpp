#pragma once
#include "Component.hpp"
#include "CPlayerContext.hpp"

class ContactListenerPlayScene : public b2ContactListener {
	entt::registry& m_registry;
public:
	ContactListenerPlayScene(entt::registry& registry)
		: m_registry(registry)
	{}

	void BeginContact(b2Contact* contact) override {
		for (auto* fixture : { contact->GetFixtureA() , contact->GetFixtureB() }) {
			if (fixture->GetUserData().pointer == 10000) {
				++m_registry.get<CPlayerContext>((entt::entity)fixture->GetBody()->GetUserData().pointer).numObjectsOnFoot;
			}
		}
	}

	void EndContact(b2Contact* contact) override {
		for (auto* fixture : { contact->GetFixtureA() , contact->GetFixtureB() }) {
			if (fixture->GetUserData().pointer == 10000) {
				--m_registry.get<CPlayerContext>((entt::entity)fixture->GetBody()->GetUserData().pointer).numObjectsOnFoot;
			}
		}
	}
};
