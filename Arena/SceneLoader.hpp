#pragma once
#include <memory>
#include "SceneMenu.hpp"
#include "ScenePlay.hpp"

class SceneLoader
{
public:
	static std::shared_ptr<Scene> createScene(SceneID id, BaseGameSystem& gameSystem);
};

