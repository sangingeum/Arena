#pragma once
#include "UINode.hpp"
#include <deque>
#include <memory>

class UIInternalNode : public UINode
{
protected:
	using Children = std::deque<std::unique_ptr<UINode>>;
	Children m_children;
public:
	UIInternalNode(const sf::Transform& transform = sf::Transform::Identity)
		: UINode(transform)
	{}

	void render(sf::RenderWindow& window, sf::Transform transform) override {
		if (getHidden())
			return;
		// Render self
		auto finalTransform = transform * getTransform();
		window.draw(m_sprite, finalTransform);
		// Render childern
		for (auto& child : m_children)
			child->render(window, finalTransform);
	}

	bool mouseClick(ActionArgument args) override {
		if (getHidden())
			return false;
		auto [pressed, x, y] = args;
		auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
		x = transformedPoint.x;
		y = transformedPoint.y;
		if (m_sprite.getGlobalBounds().contains({ x, y })) {
			for (auto child = m_children.rbegin(); child != m_children.rend(); ++child) {
				if ((*child)->mouseClick({ pressed, x, y })) {
					return true;
				}
			}
			return true;
		}
		return false;
	}

	bool mouseMove(ActionArgument args, bool handled) override {
		if (getHidden())
			return false;
		auto [_, x, y] = args;
		auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
		x = transformedPoint.x;
		y = transformedPoint.y;
		if (m_sprite.getGlobalBounds().contains({ x, y })) {
			for (auto child = m_children.rbegin(); child != m_children.rend(); ++child) {
				handled |= (*child)->mouseMove({ _, x, y }, handled);
			}
			return true;
		}
		return false;
	}

	inline void addChildBack(std::unique_ptr<UINode>&& node) {
		m_children.emplace_back(std::move(node));
	}

	inline void addChildFront(std::unique_ptr<UINode>&& node) {
		m_children.emplace_front(std::move(node));
	}

	inline void popChildBack() {
		m_children.pop_back();
	}

	inline void popChildFront() {
		m_children.pop_front();
	}

};

