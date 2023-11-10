#pragma once
#include "UINode.hpp"
#include <memory>

class UIInternalNode : public UINode
{
protected:
	using Children = std::vector<std::unique_ptr<UINode>>;
	Children m_children;
public:
	UIInternalNode(const sf::Transform& transform = sf::Transform::Identity)
		: UINode(transform)
	{}

	void render(sf::RenderWindow& window, sf::Transform transform) override {
		// Render self
		auto finalTransform = transform * getTransform();
		window.draw(m_sprite, finalTransform);
		// Render childern
		for (auto& child : m_children)
			child->render(window, finalTransform);
	}

	bool mouseClick(ActionArgument args) override {
		auto [pressed, x, y] = args;
		auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
		x = transformedPoint.x;
		y = transformedPoint.y;
		if (m_sprite.getGlobalBounds().contains({ x, y })) {
			for (auto& child : m_children) {
				if (child->mouseClick({ pressed, x, y })) {
					break;
				}
			}
			return true;
		}
		return false;
	}

	void mouseMove(ActionArgument args) override {
		auto [_, x, y] = args;
		auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
		x = transformedPoint.x;
		y = transformedPoint.y;
		if (m_sprite.getGlobalBounds().contains({ x, y })) {
			for (auto& child : m_children) {
				child->mouseMove({ _, x, y });
			}
		}
	}

	void addChild(std::unique_ptr<UINode>&& node) {
		m_children.emplace_back(std::move(node));
	}

};

