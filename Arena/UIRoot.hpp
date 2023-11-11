#pragma once
#include "UIInternalNode.hpp"
#include "UILeaf.hpp"

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
	UIRoot()
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
		if (!pressed) {
			m_dragging = false;
			m_draggedNode = nullptr;
			return false;
		}
		for (auto child = m_children.rbegin(); child != m_children.rend(); ++child) {
			if ((*child)->mouseClick({ pressed, x, y })) {
				if ((*child)->getDraggable()) {
					m_dragging = true;
					m_draggedNode = (*child).get();
					m_prevMousePos = { x, y };
				}
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

	bool mouseMove(ActionArgument args, bool handled = false) override {
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

