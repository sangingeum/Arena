#pragma once
#include "UINode.hpp"
#include "Config.hpp"
#include <functional>

class UILeaf : public UINode
{
protected:
	std::function<void()> m_onHotHandler{ []() {} };
	std::function<void()> m_onColdHandler{ []() {} };
	std::function<void()> m_onClickHandler{ []() {} };
	sf::Text m_text{};
public:
	UILeaf(const sf::Transform& transform = sf::Transform::Identity);
	// Primary functions
	void render(sf::RenderWindow& window, sf::Transform transform) override;
	bool mouseClick(ActionArgument args) override;
	bool mouseMove(ActionArgument args, bool handled) override;
	// Event handlers
	inline void setOnHotHandler(std::function<void()> handler);
	inline void setOnColdHandler(std::function<void()> handler);
	inline void setOnClickHandler(std::function<void()> handler);
	virtual void onHot();
	virtual void onCold();
	virtual void onClick();
	// Setter & Getter
	void setText(sf::String string);
protected:
	void centerText();
};

// inline functions

void UILeaf::setOnHotHandler(std::function<void()> handler) {
	m_onHotHandler = std::move(handler);
}

void UILeaf::setOnColdHandler(std::function<void()> handler) {
	m_onColdHandler = std::move(handler);
}

void UILeaf::setOnClickHandler(std::function<void()> handler) {
	m_onClickHandler = std::move(handler);
}