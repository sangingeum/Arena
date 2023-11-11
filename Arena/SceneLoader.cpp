#include "SceneLoader.hpp"

std::shared_ptr<Scene> SceneLoader::createScene(SceneID id, BaseGameSystem& gameSystem) {
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
		throw std::runtime_error("Unknown scene ID");
		break;
	}
}
