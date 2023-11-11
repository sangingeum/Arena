#include "UIInternalNode.hpp"

UIInternalNode::UIInternalNode(const sf::Transform& transform)
	: UINode(transform)
{}

void UIInternalNode::render(sf::RenderWindow& window, sf::Transform transform) {
	if (getHidden())
		return;
	// Render self
	auto finalTransform = transform * getTransform();
	window.draw(m_sprite, finalTransform);
	// Render childern
	for (auto& child : m_children)
		child->render(window, finalTransform);
}

bool UIInternalNode::mouseClick(ActionArgument args) {
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

bool UIInternalNode::mouseMove(ActionArgument args, bool handled) {
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

void UIInternalNode::popLater(UINode* ptr) {
	m_toRemove.push_back(ptr);
}

void UIInternalNode::addLater(std::unique_ptr<UINode>&& ptr) {
	m_toAdd.emplace_back(std::move(ptr));
}

void UIInternalNode::update(unsigned width, unsigned height) {
	// Flush dead children
	for (auto* ptr : m_toRemove) {
		m_children.erase
		(std::remove_if(m_children.begin(), m_children.end(),
			[ptr](std::unique_ptr<UINode>& child) {
				return child.get() == ptr; }),
				m_children.end());
	}
	m_toRemove.clear();
	// Add new children
	if (m_toAdd.size() > 0) {
		for (auto& ptr : m_toAdd) {
			addChildBack(std::move(ptr));
		}
		changeResolution(width, height);
	}
	m_toAdd.clear();
}

void UIInternalNode::changeResolution(unsigned width, unsigned height)
{
	// Update the current transform
	auto transform = getAnchorTransform();
	transform.translate(m_anchor.x * width, m_anchor.y * height);
	m_transform = std::move(transform);
	// Update children
	auto size = m_sprite.getGlobalBounds().getSize();
	for (auto& child : m_children) {
		child->changeResolution(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
	}
}

