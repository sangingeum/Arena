#pragma once
#include <box2d/box2d.h>

// You should manually reset 'shortest' to reuse this
class RayCastCallbackGetShortest : public b2RayCastCallback
{
public:
	float shortest{ 100000.f };
	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override {
		shortest = fraction;
		return fraction;
	}
};

