#pragma once
#include "Component.hpp"
#include "CPlayerContext.hpp"
#include <iostream>

class ContactListenerPlayScene : public b2ContactListener {
	entt::registry& m_registry;
public:
	ContactListenerPlayScene(entt::registry& registry)
		: m_registry(registry)
	{}

	void BeginContact(b2Contact* contact) override {
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		for (b2Fixture* fixture : { fixtureA, fixtureB }) {
			auto ptr = fixture->GetUserData().pointer;
			if (ptr == 10000) {
				++m_registry.get<CPlayerContext>((entt::entity)fixture->GetBody()->GetUserData().pointer).numObjectsOnFoot;
			}
			else if (ptr == 9000) {
				//bool lookingRight = m_registry.get<CPlayerContext>((entt::entity)fixture->GetBody()->GetUserData().pointer).lookingRight;
				b2Fixture* counterpartFixture = (fixture == fixtureA) ? fixtureB : fixtureA;
				b2Vec2 counterpartPos = counterpartFixture->GetBody()->GetPosition();
				//b2Vec2 direction = lookingRight ? b2Vec2{ 1.f, 0.f } : b2Vec2{ -1.f, 0.f };
				b2Vec2 impulse = m_registry.get<CImpulse>((entt::entity)fixture->GetBody()->GetUserData().pointer).impulse;
				std::cout << "collision \n";
				counterpartFixture->GetBody()->ApplyLinearImpulse(impulse, counterpartPos, true);
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
