#pragma once
#include <SFML/Graphics.hpp>
#include "Action.hpp"

// m_transform must do only translations since I'm changing the order of multiplications 
class UINode
{
protected:
	sf::Transform m_transform;
	bool m_hidden{ false };
	bool m_hot{ false };
public:
	UINode(const sf::Transform& transform = sf::Transform::Identity)
		:m_transform(transform)
	{}
	virtual	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) = 0;
	virtual	bool mouseClick(ActionArgument args) = 0;
	virtual	void mouseMove(ActionArgument args) = 0;
	virtual void setHidden(bool hide) {
		m_hidden = hide;
	}
	virtual void setHot(bool hot) {
		m_hot = hot;
	}
	inline virtual sf::Transform& getTransform() {
		return m_transform;
	}
	virtual ~UINode() = default;
};

