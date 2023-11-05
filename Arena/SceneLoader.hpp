#pragma once
#include <memory>
#include "SceneMenu.hpp"
#include "ScenePlay.hpp"
class SceneLoader
{
public:
	static std::shared_ptr<Scene> createScene(SceneID id) {
		switch (id)
		{
		case SceneID::mainMenu:
			return std::make_shared<SceneMenu>();
			break;
		case SceneID::play:
			return std::make_shared<ScenePlay>();
			break;
		default:
			// unknown ID
			break;
		}

	}
};

