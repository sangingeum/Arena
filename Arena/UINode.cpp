#include "UINode.hpp"

// getter & setter

UINode::UINode(const sf::Transform& transform)
	: m_transform(transform)
{}

// Update functions

void UINode::translate(float x, float y) {
	m_transform.translate(x, y);
}

void UINode::changeResolution(unsigned width, unsigned height) {
	auto transform = getAnchorTransform();
	transform.translate(m_anchor.x * width, m_anchor.y * height);
	m_transform = std::move(transform);
}

sf::Transform UINode::getAnchorTransform() const {
	auto transform = sf::Transform::Identity;
	auto size = m_sprite.getGlobalBounds().getSize();
	switch (m_anchorType)
	{
	case UIAnchorType::leftTop:
		// sfml default
		break;
	case UIAnchorType::midTop:
		transform.translate(-size.x / 2.f, 0);
		break;
	case UIAnchorType::rightTop:
		transform.translate(-size.x, 0);
		break;
	case UIAnchorType::leftMid:
		transform.translate(0, -size.y / 2.f);
		break;
	case UIAnchorType::center:
		transform.translate(-size.x / 2.f, -size.y / 2.f);
		break;
	case UIAnchorType::rightMid:
		transform.translate(-size.x, -size.y / 2.f);
		break;
	case UIAnchorType::leftBottom:
		transform.translate(0, -size.y);
		break;
	case UIAnchorType::midBottom:
		transform.translate(-size.x / 2.f, -size.y);
		break;
	case UIAnchorType::rightBottom:
		transform.translate(-size.x, -size.y);
		break;
	default:
		break;
	}
	return transform;
}
