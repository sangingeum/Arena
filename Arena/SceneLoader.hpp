#pragma once
#include <memory>
#include "SceneMenu.hpp"
#include "ScenePlay.hpp"

class SceneLoader
{
public:
	static std::shared_ptr<Scene> createScene(SceneID id, BaseGameSystem& gameSystem) {
		switch (id)
		{
		case SceneID::mainMenu:
			return std::make_shared<SceneMenu>(gameSystem);
			break;
		case SceneID::play:
			return std::make_shared<ScenePlay>(gameSystem);
			break;
		default:
			// unknown ID
			break;
		}

	}
};

