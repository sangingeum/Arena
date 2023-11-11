#pragma once
#include "UINode.hpp"
#include <deque>

class UIInternalNode : public UINode
{
protected:
	using Children = std::deque<std::unique_ptr<UINode>>;
	Children m_children;
public:
	UIInternalNode(const sf::Transform& transform = sf::Transform::Identity);
	// Primary functions
	void render(sf::RenderWindow& window, sf::Transform transform) override;
	bool mouseClick(ActionArgument args) override;
	bool mouseMove(ActionArgument args, bool handled) override;
	// Add/Pop child
	inline void addChildBack(std::unique_ptr<UINode>&& node);
	inline void addChildFront(std::unique_ptr<UINode>&& node);
	inline void popChildBack();
	inline void popChildFront();
	// Update functions
	void changeResolution(unsigned width, unsigned height) override;
};

// inline functions

inline void UIInternalNode::addChildBack(std::unique_ptr<UINode>&& node) {
	m_children.emplace_back(std::move(node));
}

inline void UIInternalNode::addChildFront(std::unique_ptr<UINode>&& node) {
	m_children.emplace_front(std::move(node));
}

inline void UIInternalNode::popChildBack() {
	m_children.pop_back();
}

inline void UIInternalNode::popChildFront() {
	m_children.pop_front();
}