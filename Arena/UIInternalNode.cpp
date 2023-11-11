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

