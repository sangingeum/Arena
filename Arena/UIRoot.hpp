#pragma once
#include "UIInternalNode.hpp"

// Root UI node
// Nodes at the back will be visible on top of nodes at the front.
// Therefore, when handling mouse inputs, nodes at the back take higher priority.
class UIRoot : public UIInternalNode
{
protected:
	sf::View m_screenView;
	bool m_dragging{ false };
	UINode* m_draggedNode{ nullptr };
	sf::Vector2f m_prevMousePos{};
public:
	UIRoot();
	// Primary functions
	void render(sf::RenderWindow& window, sf::Transform transform = sf::Transform::Identity) override;
	bool mouseClick(ActionArgument args) override;
	bool mouseMove(ActionArgument args, bool handled = false) override;
	// Update functions
	void translate(float x, float y) override;
	void changeResolution(unsigned width, unsigned height) override;
};

