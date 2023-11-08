#pragma once
#include "Scene.hpp"

class BaseGameSystem
{
public:
	virtual void run() = 0;
	virtual void quit() = 0;
	virtual void changeScene(SceneID id, bool destroyCurrentScene, bool overwriteIfExists) = 0;
	BaseGameSystem() = default;
	virtual ~BaseGameSystem() = default;
};

