#pragma once
#include "State.hpp"
#include "Component.hpp"
#include "CPlayerInput.hpp"
#include <functional>

class CPlayerContext : public CPlayerInput
{
protected:
	std::unique_ptr<State> m_state;
	std::function<CAnimation()> m_getIdleAnimation;
	std::function<CAnimation()> m_getAttackAnimation;
	std::function<CAnimation()> m_getHurtAnimation;
	std::function<CAnimation()> m_getJumpAnimation;
	std::function<CAnimation()> m_getWalkAnimation;
	std::function<CAnimation()> m_getRunAnimation;
	std::function<CAnimation()> m_getDeadAnimation;
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
	CAnimation getAnimation() {
		switch (getCurrentStateID())
		{
		case StateID::Idle:
			return getIdleAnimation();
		case StateID::Attack:
			return getAttackAnimation();
		case StateID::Hurt:
			return getHurtAnimation();
		case StateID::Jump:
			return getJumpAnimation();
		case StateID::Walk:
			return getWalkAnimation();
		case StateID::Run:
			return getRunAnimation();
		case StateID::Dead:
			return getDeadAnimation();
		default:
			return getIdleAnimation(); // error
		}
	}
	inline void setIdleAnimationGetter(std::function<CAnimation()> getIdleAnimation);
	inline void setAttackAnimationGetter(std::function<CAnimation()> getAttackAnimation);
	inline void setHurtAnimationGetter(std::function<CAnimation()> getHurtAnimation);
	inline void setJumpAnimationGetter(std::function<CAnimation()> getJumpAnimation);
	inline void setWalkAnimationGetter(std::function<CAnimation()> getWalkAnimation);
	inline void setRunAnimationGetter(std::function<CAnimation()> getRunAnimation);
	inline void setDeadAnimationGetter(std::function<CAnimation()> getDeadAnimation);
protected:
	inline CAnimation getIdleAnimation();
	inline CAnimation getAttackAnimation();
	inline CAnimation getHurtAnimation();
	inline CAnimation getJumpAnimation();
	inline CAnimation getWalkAnimation();
	inline CAnimation getRunAnimation();
	inline CAnimation getDeadAnimation();
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
		case StateID::Hurt:
			break;
		case StateID::Jump:
			m_state = std::make_unique<StatePlayerJump>(*this);
			needAnimationUpdate = true;
			break;
		case StateID::Walk:
			m_state = std::make_unique<StatePlayerWalk>(*this);
			needAnimationUpdate = true;
			break;
		case StateID::Run:
			m_state = std::make_unique<StatePlayerRun>(*this);
			needAnimationUpdate = true;
			break;
		case StateID::Dead:
			break;
		default:
			break;
		}
	}
};

inline void CPlayerContext::setIdleAnimationGetter(std::function<CAnimation()> getIdleAnimation) {
	m_getIdleAnimation = std::move(getIdleAnimation);
}
inline CAnimation CPlayerContext::getIdleAnimation() {
	return m_getIdleAnimation();
}
inline void CPlayerContext::setAttackAnimationGetter(std::function<CAnimation()> getAttackAnimation) {
	m_getAttackAnimation = std::move(getAttackAnimation);
}
inline CAnimation CPlayerContext::getAttackAnimation() {
	return m_getAttackAnimation();
}
inline void CPlayerContext::setHurtAnimationGetter(std::function<CAnimation()> getHurtAnimation) {
	m_getHurtAnimation = std::move(getHurtAnimation);
}
inline CAnimation CPlayerContext::getHurtAnimation() {
	return m_getHurtAnimation();
}
inline void CPlayerContext::setJumpAnimationGetter(std::function<CAnimation()> getJumpAnimation) {
	m_getJumpAnimation = std::move(getJumpAnimation);
}
inline CAnimation CPlayerContext::getJumpAnimation() {
	return m_getJumpAnimation();
}
inline void CPlayerContext::setWalkAnimationGetter(std::function<CAnimation()> getWalkAnimation) {
	m_getWalkAnimation = std::move(getWalkAnimation);
}
inline CAnimation CPlayerContext::getWalkAnimation() {
	return m_getWalkAnimation();
}
inline void CPlayerContext::setRunAnimationGetter(std::function<CAnimation()> getRunAnimation) {
	m_getRunAnimation = std::move(getRunAnimation);
}
inline CAnimation CPlayerContext::getRunAnimation() {
	return m_getRunAnimation();
}
inline void CPlayerContext::setDeadAnimationGetter(std::function<CAnimation()> getDeadAnimation) {
	m_getDeadAnimation = std::move(getDeadAnimation);
}
inline CAnimation CPlayerContext::getDeadAnimation() {
	return m_getDeadAnimation();
}