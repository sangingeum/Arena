#pragma once
#include "UIInternalNode.hpp"
#include "UILeaf.hpp"

// Root UI node
class UIGraph : public UIInternalNode
{
protected:
	sf::View m_screenView;
public:
	UIGraph()
		: UIInternalNode(sf::Transform::Identity)
	{}

	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) override {
		// Change to screen space
		auto curView = window.getView();
		window.setView(m_screenView);
		// Render
		for (auto& child : m_children)
			child->render(window, transform);
		// Change back to the orginal view
		window.setView(curView);
	}

	bool mouseClick(ActionArgument args) override {
		auto [pressed, x, y] = args;
		if (!pressed)
			return false;
		for (auto& child : m_children) {
			if (child->mouseClick({ pressed, x, y })) {
				return true;
			}
		}
		return false;
	}

	void mouseMove(ActionArgument args) override {
		auto [_, x, y] = args;
		for (auto& child : m_children) {
			child->mouseMove({ _, x, y });
		}
	}

	void translate(float x, float y) override {
		for (auto& child : m_children) {
			child->translate(x, y);
		}
	}

	void changeResolution(unsigned width, unsigned height) override {
		// Update screenView
		m_screenView = sf::View{ sf::FloatRect{0, 0, static_cast<float>(width), static_cast<float>(height)} };
		// Update UI node postions
		for (auto& child : m_children) {
			child->changeResolution(width, height);
		}
	}

};

