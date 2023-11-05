#pragma once
#include "Action.hpp"
#include <SFML/Graphics.hpp>

enum class SceneID {
	mainMenu,
	play,
};


class Scene
{
public:
	virtual void sRender(sf::RenderWindow& window) = 0;
	virtual void sUpdate() = 0;
	virtual void sPhysics() = 0;
	virtual void sHandleAction(Action action) = 0;
};

