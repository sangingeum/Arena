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
	virtual ~UINode() = default;
	// 
	virtual	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) = 0;
	virtual	bool mouseClick(ActionArgument args) = 0;
	virtual	void mouseMove(ActionArgument args) = 0;
	// getter & setter
	inline virtual void setHidden(bool hide) {
		m_hidden = hide;
	}
	inline virtual void setHot(bool hot) {
		m_hot = hot;
	}
	inline virtual bool getHidden() {
		return m_hidden;
	}
	inline virtual bool getHot() {
		return m_hot;
	}
	inline virtual sf::Transform& getTransform() {
		return m_transform;
	}
	// Event handlers
	virtual void onHot() {}
	virtual void onCold() {}
	virtual void onClick() {}
};

