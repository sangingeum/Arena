#pragma once
#include "Action.hpp"
#include <box2d/box2d.h>

enum class StateID {
	Idle,
	Attack,
	BeingAttacked,
	Jump,
	Move
};
