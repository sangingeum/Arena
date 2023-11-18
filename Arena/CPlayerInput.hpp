#pragma once
#include <SFML/Graphics.hpp>
#include "Action.hpp"

struct CPlayerInput
{
private:
	sf::Transform left{ sf::Transform::Identity };
public:
	CPlayerInput() {
		left.scale({ -1.f, 1.f });
	}
	virtual ~CPlayerInput() = default;
	uint32_t numObjectsOnFoot{ 0 };
	float UpJumpCooldown{ 0.f };
	float DownJumpCooldown{ 0.f };
	float AttackCooldown{ 0.f };
	float walkingSpeed{ 4.f };
	float runningSpeed{ 8.f };
	float upJumpSpeed{ 12.f };
	float downJumpSpeed{ 50.f };
	// Pressed Keys 
	bool moveUp{ false };
	bool moveDown{ false };
	bool moveLeft{ false };
	bool moveRight{ false };
	bool jump{ false };
	bool shift{ false };
	bool attack1{ false };
	bool attack2{ false };
	bool attack3{ false };
	// Indicator
	bool needAnimationUpdate{ false };
	// Character direction
	bool lookingRight{ true };

	void updateKey(ActionID id, bool pressed) {
		switch (id)
		{
		case ActionID::characterMoveUp:
			moveUp = pressed;
			break;
		case ActionID::characterMoveLeft:
			moveLeft = pressed;
			if (pressed) {
				lookingRight = false;
			}
			break;
		case ActionID::characterMoveDown:
			moveDown = pressed;
			break;
		case ActionID::characterMoveRight:
			moveRight = pressed;
			if (pressed) {
				lookingRight = true;
			}
			break;
		case ActionID::characterJump:
			jump = pressed;
			break;
		case ActionID::leftShift:
			shift = pressed;
			break;
		case ActionID::characterAttack1:
			attack1 = pressed;
			break;
		case ActionID::characterAttack2:
			attack2 = pressed;
			break;
		case ActionID::characterAttack3:
			attack3 = pressed;
			break;
		default:
			break;
		}
	}
	inline sf::Transform getDirection() {
		return lookingRight ? sf::Transform::Identity : left;
	}

	void updateCooldown(float timeStep) {
		UpJumpCooldown = std::max(0.f, UpJumpCooldown - timeStep);
		DownJumpCooldown = std::max(0.f, DownJumpCooldown - timeStep);
		AttackCooldown = std::max(0.f, AttackCooldown - timeStep);
	}

	inline void resetUpJumpCooldown() {
		UpJumpCooldown = 0.05f;
	}
	inline bool canUpJump() {
		return jump && (numObjectsOnFoot) && (UpJumpCooldown < std::numeric_limits<float>::epsilon());
	}
	inline void resetDownJumpCooldown() {
		DownJumpCooldown = 0.05f;
	}
	inline bool canDownJump() {
		return moveDown && (!numObjectsOnFoot) && (DownJumpCooldown < std::numeric_limits<float>::epsilon());
	}
	inline void resetAttackCooldown() {
		AttackCooldown = 0.4f;
	}
};
