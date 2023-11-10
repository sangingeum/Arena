#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Action.hpp"
// m_transform must do only translations since I'm changing the order of multiplications 

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
	sf::Transform m_transform;
	sf::Vector2f m_anchor{ 0.f, 0.f };
	sf::RectangleShape m_rect{ {0.f, 0.f} };
	UIAnchorType m_anchorType{ UIAnchorType::leftTop };
	bool m_hidden{ false };
	bool m_hot{ false };
public:
	UINode(const sf::Transform& transform = sf::Transform::Identity)
		: m_transform(transform)
	{}
	virtual ~UINode() = default;
	// Primary functions
	virtual	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) = 0;
	virtual	bool mouseClick(ActionArgument args) = 0;
	virtual	void mouseMove(ActionArgument args) = 0;
	// Update functions
	virtual	void translate(float x, float y) {
		m_transform.translate(x, y);
	}
	virtual	void changeResolution(unsigned width, unsigned height) {
		auto transform = getAnchorTransform();
		transform.translate(m_anchor.x * width, m_anchor.y * height);
		m_transform = std::move(transform);
	}
	virtual	void setAnchorType(UIAnchorType type) {
		m_anchorType = type;
	}
	// getter & setter
	inline void setHidden(bool hide) {
		m_hidden = hide;
	}
	inline void setHot(bool hot) {
		m_hot = hot;
	}
	inline bool getHidden() {
		return m_hidden;
	}
	inline bool getHot() {
		return m_hot;
	}
	inline sf::Transform& getTransform() {
		return m_transform;
	}
	inline sf::RectangleShape& getRect() {
		return m_rect;
	}
	inline void setAnchor(float x, float y) {
		m_anchor.x = std::clamp(x, 0.0f, 1.0f);
		m_anchor.y = std::clamp(y, 0.0f, 1.0f);
	}
protected:
	sf::Transform getAnchorTransform() const {
		auto transform = sf::Transform::Identity;
		auto size = m_rect.getSize();
		switch (m_anchorType)
		{
		case UIAnchorType::leftTop:
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
};

