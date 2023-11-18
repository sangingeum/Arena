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
	virtual void sUpdate(float timeStep) = 0;
	virtual void sAnimation(float timeStep) = 0;
	virtual void sCooldown(float timeStep) = 0;
	virtual void sPhysics(float timeStep) = 0;
	virtual void sHandleAction(sf::RenderWindow& window, Action action) = 0;
	virtual void changeResolution(unsigned width, unsigned height) = 0;
	virtual void adjustView(sf::RenderWindow& window) = 0;
};

