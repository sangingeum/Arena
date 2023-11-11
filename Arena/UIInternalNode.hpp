#pragma once
#include "UINode.hpp"
#include <deque>
#include <vector>

class UIInternalNode : public UINode
{
protected:
	using Children = std::deque<std::unique_ptr<UINode>>;
	using toRemove = std::vector<UINode*>;
	using toAdd = std::vector<std::unique_ptr<UINode>>;
	Children m_children;
	toRemove m_toRemove;
	toAdd m_toAdd;
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
	void popLater(UINode* ptr);
	void addLater(std::unique_ptr<UINode>&& ptr);
	void update(unsigned width, unsigned height);
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