#pragma once
#include "CPlayerInput.hpp"
#include <box2d/box2d.h>

enum class StateID {
	noState, // It does not trigger state changes
	Idle,
	Attack_1,
	Attack_2,
	Attack_3,
	Hurt,
	Jump,
	Walk,
	Run,
	Dead,
	Shield,
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

class StatePlayerIdle : public State {
public:
	StatePlayerIdle(CPlayerInput& context)
		: State(StateID::Idle, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (m_context.attack1)
			return StateID::Attack_1;
		if (m_context.attack2)
			return StateID::Attack_2;
		if (m_context.attack3)
			return StateID::Attack_3;
		if (m_context.moveDown)
			return StateID::Shield;
		if (!m_context.numObjectsOnFoot)
			return StateID::Jump;
		else if (m_context.moveLeft || m_context.moveRight) {
			if (m_context.moveLeft && m_context.moveRight)
				StateID::noState;
			if (m_context.shift)
				return StateID::Run;
			return StateID::Walk;
		}
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerJump : public State {
public:
	StatePlayerJump(CPlayerInput& context)
		: State(StateID::Jump, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (m_context.attack1)
			return StateID::Attack_1;
		if (m_context.attack2)
			return StateID::Attack_2;
		if (m_context.attack3)
			return StateID::Attack_3;
		if (m_context.moveDown)
			return StateID::Shield;
		if (m_context.numObjectsOnFoot)
			return StateID::Idle;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
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
		// Down jump
		if (m_context.moveDown && (!m_context.numObjectsOnFoot) && m_context.DownJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetDownJumpCooldown();
			curVelocity.y = m_context.downJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerWalk : public State {
public:
	StatePlayerWalk(CPlayerInput& context)
		: State(StateID::Walk, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (m_context.attack1)
			return StateID::Attack_1;
		if (m_context.attack2)
			return StateID::Attack_2;
		if (m_context.attack3)
			return StateID::Attack_3;
		if (m_context.moveDown)
			return StateID::Shield;
		if (!m_context.numObjectsOnFoot)
			return StateID::Jump;
		else if (!m_context.moveLeft && !m_context.moveRight) {
			return StateID::Idle;
		}
		else if (m_context.shift) {
			return StateID::Run;
		}
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
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
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerRun : public State {
public:
	StatePlayerRun(CPlayerInput& context)
		: State(StateID::Run, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (m_context.attack1)
			return StateID::Attack_1;
		if (m_context.attack2)
			return StateID::Attack_2;
		if (m_context.attack3)
			return StateID::Attack_3;
		if (m_context.moveDown)
			return StateID::Shield;
		if (!m_context.numObjectsOnFoot)
			return StateID::Jump;
		else if (!m_context.moveLeft && !m_context.moveRight) {
			return StateID::Idle;
		}
		else if (!m_context.shift) {
			return StateID::Walk;
		}
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
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
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerShield : public State {
public:
	StatePlayerShield(CPlayerInput& context)
		: State(StateID::Shield, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (!m_context.moveDown)
			return StateID::Idle;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
		if (m_context.moveLeft)
			curVelocity.x = -m_context.walkingSpeed / 4.f;
		if (m_context.moveRight)
			curVelocity.x = m_context.walkingSpeed / 4.f;
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerAttack_1 : public State {
public:
	StatePlayerAttack_1(CPlayerInput& context)
		: State(StateID::Attack_1, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (!m_context.attack1)
			return StateID::Idle;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
		if (m_context.moveLeft)
			curVelocity.x = -m_context.walkingSpeed / 2.f;
		if (m_context.moveRight)
			curVelocity.x = m_context.walkingSpeed / 2.f;
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerAttack_2 : public State {
public:
	StatePlayerAttack_2(CPlayerInput& context)
		: State(StateID::Attack_2, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (!m_context.attack2)
			return StateID::Idle;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
		if (m_context.moveLeft)
			curVelocity.x = -m_context.walkingSpeed / 2.f;
		if (m_context.moveRight)
			curVelocity.x = m_context.walkingSpeed / 2.f;
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};

class StatePlayerAttack_3 : public State {
public:
	StatePlayerAttack_3(CPlayerInput& context)
		: State(StateID::Attack_3, context)
	{}
	StateID handleAction(ActionID id, bool pressed) override {
		return StateID::noState;
	}
	StateID update() override {
		if (!m_context.attack3)
			return StateID::Idle;
		return StateID::noState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) override {
		// Left Right move
		if (m_context.moveLeft)
			curVelocity.x = -m_context.walkingSpeed / 2.f;
		if (m_context.moveRight)
			curVelocity.x = m_context.walkingSpeed / 2.f;
		// Up jump
		if (m_context.jump && (m_context.numObjectsOnFoot) && m_context.UpJumpCooldown < std::numeric_limits<float>::epsilon()) {
			m_context.resetUpJumpCooldown();
			curVelocity.y = -m_context.upJumpSpeed;
		}
		return std::move(curVelocity);
	}
};