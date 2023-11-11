#include "UILeaf.hpp"

UILeaf::UILeaf(const sf::Transform& transform)
	: UINode(transform)
{
	setOnHotHandler([&]() {m_sprite.setColor(sf::Color::Yellow); });
	setOnColdHandler([&]() {m_sprite.setColor(sf::Color::White); });
	setOnClickHandler([&]() {m_sprite.setColor(sf::Color::Yellow); });
}

void UILeaf::render(sf::RenderWindow& window, sf::Transform transform) {
	if (getHidden())
		return;
	auto finalTransform = transform * getTransform();
	window.draw(m_sprite, finalTransform);
}

bool UILeaf::mouseClick(ActionArgument args) {
	if (getHidden())
		return false;
	auto [pressed, x, y] = args;
	auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
	x = transformedPoint.x;
	y = transformedPoint.y;
	if (m_sprite.getGlobalBounds().contains({ x, y })) {
		onClick();
		return true;
	}
	return false;
}

bool UILeaf::mouseMove(ActionArgument args, bool handled) {
	if (getHidden())
		return false;
	auto [_, x, y] = args;
	auto transformedPoint = getTransform().getInverse().transformPoint({ x, y });
	x = transformedPoint.x;
	y = transformedPoint.y;
	if (!handled && m_sprite.getGlobalBounds().contains({ x, y })) {
		setHot(true);
		onHot();
		return true;
	}
	else if (getHot()) {
		setHot(false);
		onCold();
	}
	return false;
}

// Event handlers

void UILeaf::onHot() { m_onHotHandler(); }

void UILeaf::onCold() { m_onColdHandler(); }

void UILeaf::onClick() { m_onClickHandler(); }
