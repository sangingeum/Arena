#pragma once
#include "UINode.hpp"
#include <functional>

class UILeaf : public UINode
{
protected:
	std::function<void()> m_onHotHandler{ []() {} };
	std::function<void()> m_onColdHandler{ []() {} };
	std::function<void()> m_onClickHandler{ []() {} };
public:
	UILeaf(const sf::Transform& transform = sf::Transform::Identity)
		: UINode(transform)
	{
		setOnHotHandler([&]() {m_rect.setFillColor(sf::Color::Cyan); });
		setOnColdHandler([&]() {m_rect.setFillColor(sf::Color::White); });
		setOnClickHandler([&]() {m_rect.setFillColor(sf::Color::Red); });
	}

	void render(sf::RenderWindow& window, sf::Transform transform) override {
		auto finalTransform = transform * getTransform();
		window.draw(m_rect, finalTransform);
	}

	bool mouseClick(ActionArgument args) override {
		auto [pressed, x, y] = args;
		auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
		x = transformedPoint.x;
		y = transformedPoint.y;
		if (m_rect.getGlobalBounds().contains({ x, y })) {
			onClick();
			return true;
		}
		return false;
	}

	void mouseMove(ActionArgument args) override {
		auto [_, x, y] = args;
		auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
		x = transformedPoint.x;
		y = transformedPoint.y;
		if (m_rect.getGlobalBounds().contains({ x, y })) {
			setHot(true);
			onHot();
		}
		else if (getHot()) {
			setHot(false);
			onCold();
		}
	}

	// Event handlers
	inline void setOnHotHandler(std::function<void()> handler) {
		m_onHotHandler = std::move(handler);
	}
	inline void setOnColdHandler(std::function<void()> handler) {
		m_onColdHandler = std::move(handler);
	}
	inline void setOnClickHandler(std::function<void()> handler) {
		m_onClickHandler = std::move(handler);
	}
	virtual void onHot() { m_onHotHandler(); }
	virtual void onCold() { m_onColdHandler(); }
	virtual void onClick() { m_onClickHandler(); }
};

