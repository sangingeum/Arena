#pragma once
#include <SFML/Graphics.hpp>
#include "Action.hpp"

class UINode
{
	bool m_hidden{ false };
public:
	virtual	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) = 0;
	virtual	bool mouseClick(ActionArgument args) = 0;
	virtual	void mouseMove(ActionArgument args) = 0;
	virtual void setHidden(bool hide) {
		m_hidden = hide;
	}
	virtual ~UINode() = default;
};

