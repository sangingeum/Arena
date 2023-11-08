#pragma once
#include <tuple>

enum class ActionID {
	noAction, // Default 
	characterMoveUp,
	characterMoveLeft,
	characterMoveDown,
	characterMoveRight,
	characterJump,
	characterAttack,
	cameraZoom,
	cameraMoveUp,
	cameraMoveLeft,
	cameraMoveDown,
	cameraMoveRight,
	mousePrimary,
	mouseSecondary,
	mouseMove,
	windowClose,
	number1,
	number2,
	number3,
	number4,
};

class Action
{
	using ActionArgument = std::tuple<bool, float, float>;
public:
	Action(ActionID id_, const ActionArgument& args_)
		: id(id_), args(args_)
	{}
	ActionID id;
	ActionArgument args;
};

