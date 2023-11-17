#pragma once
#include "CPlayerInput.hpp"
#include "State.hpp"
#include <memory>

class CPlayerContext : public CPlayerInput
{
protected:
	std::unique_ptr<State> m_state;
public:
	CPlayerContext()
	{
		m_state = std::make_unique<StatePlayerIdle>(*this);
	}
	inline StateID getCurrentStateID() const {
		return m_state->getCurrentState();
	}
	StateID handleAction(ActionID id, bool pressed) {
		updateKey(id, pressed); // Update key & direction
		StateID newState = m_state->handleAction(id, pressed);
		changeState(newState);
		return newState;
	}
	StateID update() {
		StateID newState = m_state->update();
		changeState(newState);
		return newState;
	}
	b2Vec2 calculateNextVelocity(b2Vec2 curVelocity) {
		return m_state->calculateNextVelocity(std::move(curVelocity));
	}
	bool retrieveAndResetNeedAnimationUpdate() {
		bool need = needAnimationUpdate;
		needAnimationUpdate = false;
		return need;
	}
private:
	void changeState(StateID id) {
		switch (id)
		{
		case StateID::noState:
			break;
		case StateID::Idle:
			m_state = std::make_unique<StatePlayerIdle>(*this);
			needAnimationUpdate = true;
			break;
		case StateID::Attack:
			break;
		case StateID::InPain:
			break;
		case StateID::Jump:
			m_state = std::make_unique<StatePlayerJump>(*this);
			needAnimationUpdate = true;
			break;
		case StateID::Move:
			break;
		case StateID::Dead:
			break;
		default:
			break;
		}
	}
};

