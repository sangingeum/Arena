#pragma once
#include "Action.hpp"
#include <SFML/Graphics.hpp>

enum class SceneID {
	nothing,
	mainMenu,
	play,
};

class Scene
{
public:
	virtual ~Scene() = default;
	virtual void sRender(sf::RenderWindow& window) = 0;
	virtual void sUpdate() = 0;
	virtual void sPhysics(float timeStep) = 0;
	virtual void sHandleAction(sf::RenderWindow& window, Action action) = 0;
};

