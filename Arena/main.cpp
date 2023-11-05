#include <box2d/box2d.h>
#include <format>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameSystem.hpp"
#include <memory>
#include <vector>
#include <entt.hpp>
#include "ActionBinder.hpp"
//b2Settings.h change max

struct Box {
	b2Body* body;
	sf::RectangleShape shape;
	uint32_t numContacts{ 0 };
	Box(b2World& world, entt::entity entity, float halfWidth, float halfHeight, float xPos, float yPos, b2BodyType type = b2BodyType::b2_dynamicBody, float xVel = 0.f, float yVel = 0.f)
		: shape({ 2.f * halfWidth, 2.f * halfHeight })
	{
		// Body
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
		//body->ApplyForceToCenter({ xVel*1000, yVel }, true);
		body->SetLinearVelocity({ xVel, yVel });
		body->GetUserData().pointer = (uintptr_t)entity;
		//body->SetTransform({ xPos, yPos }, 0);
		// Shape
		shape.setOrigin({ halfWidth, halfHeight });
		shape.setPosition({ 0, 0 });
	}
	void setVelocity(float xVel, float yVel) {
		body->SetLinearVelocity({ xVel, yVel });
	}

};

class myContactListener : public b2ContactListener {
	entt::registry& m_registry;
public:
	myContactListener(entt::registry& registry)
		: m_registry(registry)
	{}

	void BeginContact(b2Contact* contact) override {
		for (auto* fixture : { contact->GetFixtureA() , contact->GetFixtureB() }) {
			entt::entity entity = (entt::entity)fixture->GetBody()->GetUserData().pointer;
			auto& box = m_registry.get<Box>(entity);
			++box.numContacts;
			box.shape.setFillColor(sf::Color::Green);
		}

	}
	void EndContact(b2Contact* contact) override {
		for (auto* fixture : { contact->GetFixtureA() , contact->GetFixtureB() }) {
			entt::entity entity = (entt::entity)fixture->GetBody()->GetUserData().pointer;
			auto& box = m_registry.get<Box>(entity);
			--box.numContacts;
			if (!box.numContacts)
				box.shape.setFillColor(sf::Color::White);
		}
	}
};


int main() {


	sf::RenderWindow window{ sf::VideoMode(Config::instance().windowWidth, Config::instance().widowHeight), Config::instance().windowName };
	window.setFramerateLimit(Config::instance().frameRate);
	float winHalfWidth = Config::instance().windowWidth / 2.f;
	float winHalfHeight = Config::instance().widowHeight / 2.f;
	auto curView = window.getView();
	float ratio = 0.01f;
	curView.setCenter({ winHalfWidth * ratio, winHalfHeight * ratio });

	curView.zoom(ratio);
	window.setView(curView);
	entt::registry registry;

	const float radianToDegree{ 57.2958f };
	const b2Vec2 gravity{ 0, 9.8f };
	b2World world{ gravity };
	myContactListener listener{ registry };
	world.SetContactListener(&listener);

	auto entity = registry.create();
	registry.emplace<Box>(entity, world, entity, winHalfWidth * ratio, 1 * ratio, winHalfWidth * ratio, 0, b2BodyType::b2_staticBody);
	entity = registry.create();
	registry.emplace<Box>(entity, world, entity, winHalfWidth * ratio, 1 * ratio, winHalfWidth * ratio, winHalfHeight * 2.f * ratio, b2BodyType::b2_staticBody);
	entity = registry.create();
	registry.emplace<Box>(entity, world, entity, 1 * ratio, winHalfHeight * ratio, 0, winHalfHeight * ratio, b2BodyType::b2_staticBody);
	entity = registry.create();
	registry.emplace<Box>(entity, world, entity, 1 * ratio, winHalfHeight * ratio, winHalfWidth * 2.f * ratio, winHalfHeight * ratio, b2BodyType::b2_staticBody);
	for (int i = 0; i < 10; ++i) {
		auto entity = registry.create();
		registry.emplace<Box>(entity, world, entity, 10 * ratio, 10 * ratio, (100 + i * 70.f) * ratio, 200.f * ratio, b2BodyType::b2_dynamicBody);
		entity = registry.create();
		registry.emplace<Box>(entity, world, entity, 10 * ratio, 10 * ratio, (100 + i * 70.f) * ratio, 300.f * ratio, b2BodyType::b2_dynamicBody);
	}

	float timeStep = 1.f / Config::instance().frameRate;
	int32 velocityIterations = 16;
	int32 positionIterations = 6;
	bool w{ false }, a{ false }, s{ false }, d{ false };

	sf::Clock clock;
	while (window.isOpen()) {
		float zoom = 1.f;
		float elapsed = clock.restart().asSeconds();
		world.Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			ActionBinder::getAction(event);
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.scancode)
				{
				case sf::Keyboard::Scancode::W:
					w = true;
					break;
				case sf::Keyboard::Scancode::A:
					a = true;
					break;
				case sf::Keyboard::Scancode::S:
					s = true;
					break;
				case sf::Keyboard::Scancode::D:
					d = true;
					break;
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.scancode)
				{
				case sf::Keyboard::Scancode::W:
					w = false;
					break;
				case sf::Keyboard::Scancode::A:
					a = false;
					break;
				case sf::Keyboard::Scancode::S:
					s = false;
					break;
				case sf::Keyboard::Scancode::D:
					d = false;
					break;
				}
			}
			else if (event.type == sf::Event::MouseWheelScrolled) {
				sf::Mouse::Wheel wheel = event.mouseWheelScroll.wheel;
				if (std::abs(event.mouseWheelScroll.delta) <= 10) {
					zoom -= ((int)event.mouseWheelScroll.delta) / 50.f;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				auto worldPos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				auto entity = registry.create();
				registry.emplace<Box>(entity, world, entity, 30 * ratio, 30 * ratio, worldPos.x, worldPos.y, b2BodyType::b2_dynamicBody);
			}

		}

		{
			auto view = window.getView();
			auto offset = sf::Vector2f{ 0, 0 };
			if (w) {
				offset += sf::Vector2f{ 0, -5 };
			}
			if (a) {
				offset += sf::Vector2f{ -5, 0 };
			}
			if (s) {
				offset += sf::Vector2f{ 0, 5 };
			}
			if (d) {
				offset += sf::Vector2f{ 5, 0 };
			}
			view.setCenter(view.getCenter() + offset * ratio);
			view.zoom(zoom);
			window.setView(view);
		}
		window.clear();

		/*	auto topLeft = window.mapPixelToCoords({ 0, 0 });
			auto bottomRight = window.mapPixelToCoords({ Config::instance().windowWidth, Config::instance().widowHeight });
			b2AABB aabb{};
			aabb.lowerBound = { topLeft.x, topLeft.y };
			aabb.upperBound = { bottomRight.x, bottomRight.y };*/

		registry.view<Box>().each([&](const auto entiy, Box& box) {
			sf::Transform t;
			auto& pos = box.body->GetPosition();
			auto radian = box.body->GetAngle();
			t.translate({ pos.x, pos.y }).rotate(radian * radianToDegree);
			//box.body->SetAwake(true);
			window.draw(box.shape, t);
			});
		window.display();

	}


	return 0;
}

/*
b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.f, 4.f);
	bodyDef.linearVelocity.Set(10, 0);

	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.f, 1.f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.f;
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);

	float timeStep = 1.f / 30.f;
	int32 velocityIterations = 8;
	int32 positionIterations = 2;
	for (int32 i = 0; i < 60; ++i)
	{
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();
		std::cout << std::format("{:.2f} {:.2f} {:.2f}\n", position.x, position.y, angle) << "\n";
	}
*/