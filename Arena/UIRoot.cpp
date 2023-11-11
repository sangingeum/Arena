#include "UIRoot.hpp"

UIRoot::UIRoot()
	: UIInternalNode(sf::Transform::Identity)
{}

void UIRoot::render(sf::RenderWindow& window, sf::Transform transform) {
	// Change to screen space
	auto curView = window.getView();
	window.setView(m_screenView);
	// Render
	for (auto& child : m_children)
		child->render(window, transform);
	// Change back to the orginal view
	window.setView(curView);
}

bool UIRoot::mouseClick(ActionArgument args) {
	auto [pressed, x, y] = args;
	// Stop dragging if mouse is not pressed
	if (!pressed) {
		m_dragging = false;
		m_draggedNode = nullptr;
		return false;
	}
	for (auto child = m_children.rbegin(); child != m_children.rend(); ++child) {
		// Check if the child is clicked
		if ((*child)->mouseClick({ pressed, x, y })) {
			// If draggable, set related vaiables 
			if ((*child)->getDraggable()) {
				m_dragging = true;
				m_draggedNode = (*child).get();
				m_prevMousePos = { x, y };
			}
			// If focusable, move it to the back
			if ((*child)->getFocus()) {
				auto poppedChild = std::move(*child);
				m_children.erase(std::next(child).base());
				addChildBack(std::move(poppedChild));
			}

			return true;
		}
	}
	return false;
}

bool UIRoot::mouseMove(ActionArgument args, bool handled) {
	auto [_, x, y] = args;
	// Dragging
	if (m_dragging && m_draggedNode) {
		m_draggedNode->translate(x - m_prevMousePos.x, y - m_prevMousePos.y);
		m_prevMousePos = { x, y };
	}
	// Marking hot or cold
	for (auto child = m_children.rbegin(); child != m_children.rend(); ++child) {
		handled |= (*child)->mouseMove({ _, x, y }, handled);
	}
	return handled;
}

void UIRoot::translate(float x, float y) {
	for (auto& child : m_children) {
		child->translate(x, y);
	}
}

void UIRoot::changeResolution(unsigned width, unsigned height) {
	// Update screenView
	m_screenView = sf::View{ sf::FloatRect{ 0, 0, static_cast<float>(width), static_cast<float>(height) } };
	// Update UI node postions
	for (auto& child : m_children) {
		child->changeResolution(width, height);
	}
}
