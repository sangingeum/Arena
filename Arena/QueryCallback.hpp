#pragma once
#include <box2d/box2d.h>
class QueryCallbackAwake : public b2QueryCallback
{
	bool ReportFixture(b2Fixture* fixture) override {
		fixture->GetBody()->SetAwake(true);
		return true; //keep going to find all fixtures in the query area
	}
};

