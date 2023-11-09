#pragma once
#include "UIInternalNode.hpp"
#include "UILeaf.hpp"

class UIGraph : public UINode
{
private:
	using Children = std::vector<std::unique_ptr<UINode>>;
	Children m_children;
	sf::View m_screenView;
public:
	UIGraph(unsigned width, unsigned height) {
		changeResolution(width, height);
	}
	// Inherited via UINode
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
		for (auto& child : m_children) {
			if (child->mouseClick(std::move(args))) {
				return true;
			}
		}
		return false;
	}
	void mouseMove(ActionArgument args) override {}
	void addChildren(std::unique_ptr<UINode>&& node) {
		m_children.emplace_back(std::move(node));
	}
	void changeResolution(unsigned width, unsigned height) {
		// Update screenView
		m_screenView = sf::View{ sf::FloatRect{0, 0, static_cast<float>(width), static_cast<float>(height)} };
	}
};
