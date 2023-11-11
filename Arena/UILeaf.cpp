#include "UILeaf.hpp"

UILeaf::UILeaf(const sf::Transform& transform)
	: UINode(transform), m_text("", Config::instance().font, 30)
{
	setOnHotHandler([&]() {m_sprite.setColor(sf::Color::Yellow); });
	setOnColdHandler([&]() {m_sprite.setColor(sf::Color::White); });
	setOnClickHandler([&]() {m_sprite.setColor(sf::Color::Yellow); });
	m_text.setOutlineThickness(1);
	m_text.setOutlineColor(sf::Color::Black);
}

void UILeaf::render(sf::RenderWindow& window, sf::Transform transform) {
	if (getHidden())
		return;
	auto finalTransform = transform * getTransform();
	window.draw(m_sprite, finalTransform);
	window.draw(m_text, finalTransform);
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

// Text

void UILeaf::setText(sf::String string) {
	m_text.setString(std::move(string));
	centerText();
}

void UILeaf::centerText() {
	//m_text.setPosition((m_sprite.getLocalBounds().getSize()) / 2.f - (m_text.getLocalBounds().getSize() / 2.f));
	m_text.setPosition({ (m_sprite.getLocalBounds().getSize().x - m_text.getLocalBounds().getSize().x) / 2.f, 5 });
}