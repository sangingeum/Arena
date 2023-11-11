#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Action.hpp"

enum class UIAnchorType {
	leftTop,
	midTop,
	rightTop,
	leftMid,
	center,
	rightMid,
	leftBottom,
	midBottom,
	rightBottom,
};

class UINode
{
protected:
	sf::Transform m_transform; // m_transform must do only translations since the order of multiplications could change.
	sf::Sprite m_sprite{};
	sf::Vector2f m_anchor{ 0.f, 0.f };
	UIAnchorType m_anchorType{ UIAnchorType::leftTop }; // m_anchor and m_anchorType are used together to calculate the position of the node when the screen resolution changes
	bool m_hidden{ false }; // Whether the node is hidden
	bool m_hot{ false }; // Whether mouse is hovering on the node
	bool m_focus{ true }; // Whether the node should be placed front when clicked
	bool m_draggable{ false }; // Whether the node can be dragged
public:
	UINode(const sf::Transform& transform = sf::Transform::Identity);
	virtual ~UINode() = default;
	// Primary functions
	virtual	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) = 0;
	virtual	bool mouseClick(ActionArgument args) = 0;
	virtual	bool mouseMove(ActionArgument args, bool handled) = 0;
	// Update functions
	virtual	void translate(float x, float y);
	virtual	void changeResolution(unsigned width, unsigned height);
	// getter & setter
	inline void setAnchorType(UIAnchorType type);
	inline void setHidden(bool hide);
	inline bool getHidden();
	inline void setHot(bool hot);
	inline bool getHot();
	inline sf::Transform& getTransform();
	inline sf::Sprite& getSprite();
	inline void setAnchor(float x, float y);
	inline sf::Vector2f getAnchor();
	inline void setFocus(bool focus);
	inline bool getFocus();
	inline void setDraggable(bool draggable);
	inline bool getDraggable();
protected:
	sf::Transform getAnchorTransform() const;
};

// inline functions

void UINode::setAnchorType(UIAnchorType type) {
	m_anchorType = type;
}

void UINode::setHidden(bool hide) {
	m_hidden = hide;
}

bool UINode::getHidden() {
	return m_hidden;
}

void UINode::setHot(bool hot) {
	m_hot = hot;
}

bool UINode::getHot() {
	return m_hot;
}

sf::Transform& UINode::getTransform() {
	return m_transform;
}

sf::Sprite& UINode::getSprite() {
	return m_sprite;
}

void UINode::setAnchor(float x, float y) {
	m_anchor.x = std::clamp(x, 0.0f, 1.0f);
	m_anchor.y = std::clamp(y, 0.0f, 1.0f);
}

sf::Vector2f UINode::getAnchor() {
	return m_anchor;
}

void UINode::setFocus(bool focus) {
	m_focus = focus;
}

bool UINode::getFocus() {
	return m_focus;
}

void UINode::setDraggable(bool draggable) {
	m_draggable = draggable;
}

bool UINode::getDraggable() {
	return m_draggable;
}