#pragma once
#include "UINode.hpp"
#include <functional>

class UILeaf : public UINode
{
	sf::RectangleShape m_rect;
public:
	UILeaf()
		: m_rect({ 50, 50 })
	{
		m_rect.setFillColor(sf::Color::Yellow);
	}
	// Inherited via UINode
	void render(sf::RenderWindow& window, sf::Transform transform) override {
		window.draw(m_rect, transform);
	}
	bool mouseClick(ActionArgument args) override {
		auto [pressed, x, y] = args;
		if (m_rect.getGlobalBounds().contains({ x, y })) {
			m_rect.setFillColor(sf::Color::Green);
			return true;
		}
		return false;
	}
	void mouseMove(ActionArgument args) override {

	}
};

