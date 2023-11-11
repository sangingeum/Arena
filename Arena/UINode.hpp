#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Action.hpp"

// m_transform must do only translations since the order of multiplications could change.
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
	sf::Sprite m_sprite{};
	UIAnchorType m_anchorType{ UIAnchorType::leftTop };
	bool m_hidden{ false };
	bool m_hot{ false };
	bool m_focus{ true };
public:
	UINode(const sf::Transform& transform = sf::Transform::Identity)
		: m_transform(transform)
	{}
	virtual ~UINode() = default;
	// Primary functions
	virtual	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) = 0;
	virtual	bool mouseClick(ActionArgument args) = 0;
	virtual	bool mouseMove(ActionArgument args, bool handled) = 0;
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
	inline bool getHidden() {
		return m_hidden;
	}
	inline void setHot(bool hot) {
		m_hot = hot;
	}
	inline bool getHot() {
		return m_hot;
	}
	inline sf::Transform& getTransform() {
		return m_transform;
	}
	inline sf::Sprite& getSprite() {
		return m_sprite;
	}
	inline void setAnchor(float x, float y) {
		m_anchor.x = std::clamp(x, 0.0f, 1.0f);
		m_anchor.y = std::clamp(y, 0.0f, 1.0f);
	}
	inline sf::Vector2f getAnchor() {
		return m_anchor;
	}
	inline void setFocus(bool focus) {
		m_focus = focus;
	}
	inline bool getFocus() {
		return m_focus;
	}

protected:
	sf::Transform getAnchorTransform() const {
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
};

