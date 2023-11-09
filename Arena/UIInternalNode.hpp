#pragma once
#include "UINode.hpp"
#include <memory>

class UIInternalNode : public UINode
{
	using Children = std::vector<std::unique_ptr<UINode>>;
	Children m_children;
	sf::RectangleShape m_rect;
public:
	UIInternalNode()
		: m_rect({ 700, 700 })
	{
		m_rect.setFillColor(sf::Color{ 50, 50, 50, 200 });
	}
	// Inherited via UINode
	void render(sf::RenderWindow& window, sf::Transform transform) override {
		// Render self 
		window.draw(m_rect, transform);
		// Render childern
		for (auto& child : m_children)
			child->render(window, transform);
	}
	bool mouseClick(ActionArgument args) override {
		auto [pressed, x, y] = args;
		if (m_rect.getGlobalBounds().contains({ x, y })) {
			for (auto& child : m_children) {
				if (child->mouseClick(std::move(args))) {
					break;
				}
			}
			return true;
		}
		return false;
	}
	void mouseMove(ActionArgument args) override {

	}
	void addChildren(std::unique_ptr<UINode>&& node) {
		m_children.emplace_back(std::move(node));
	}

private:



	bool checkIntegrity() {

	}
};

