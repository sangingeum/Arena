#pragma once
#include "Action.hpp"
#include "CPlayerInput.hpp"
#include <box2d/box2d.h>

enum class StateID {
	noState, // It does not trigger state changes
	Idle,
	Attack,
	InPain,
	Jump,
	Move,
	Dead
};

class State {
protected:
	StateID m_currentState{ StateID::Idle };
	CPlayerInput& m_context;
public:
	State(StateID id, CPlayerInput& context)
		: m_currentState(id), m_context(context)
	{}
	virtual	inline StateID getCurrentState() {
		return m_currentState;
	}
	virtual StateID handleAction(ActionID id, bool pressed) = 0; // Handle the given action and modify members
	virtual StateID update() = 0; // Check if a state change is needed
	virtual b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) = 0; // Considering the given velocity and current members, what is the next velocity? 
	virtual ~State() = default;
};

class StatePlayerIdle :public State {
public:
	StatePlayerIdle(CPlayerInput& context)
		: State(StateID::Idle, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (!m_context.numObjectsOnFoot)
			return StateID::Jump;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right moving
		if (m_context.moveLeft)
			if (m_context.shift)
				curVelocity.x = -m_context.runningSpeed;
			else
				curVelocity.x = -m_context.walkingSpeed;
		if (m_context.moveRight)
			if (m_context.shift)
				curVelocity.x = m_context.runningSpeed;
			else
				curVelocity.x = m_context.walkingSpeed;
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		else if (m_context.moveDown && (!m_context.numObjectsOnFoot) && m_context.DownJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetDownJumpCooldown();
			curVelocity.y = m_context.downJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerJump :public State {
public:
	StatePlayerJump(CPlayerInput& context)
		: State(StateID::Jump, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (m_context.numObjectsOnFoot)
			return StateID::Idle;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		if (m_context.moveLeft)
			if (m_context.shift)
				curVelocity.x = -m_context.runningSpeed;
			else
				curVelocity.x = -m_context.walkingSpeed;
		if (m_context.moveRight)
			if (m_context.shift)
				curVelocity.x = m_context.runningSpeed;
			else
				curVelocity.x = m_context.walkingSpeed;
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		else if (m_context.moveDown && (!m_context.numObjectsOnFoot) && m_context.DownJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetDownJumpCooldown();
			curVelocity.y = m_context.downJumpSpeed;
		}
		return std::move(curVelocity);
	}
};
