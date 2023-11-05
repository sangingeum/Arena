#pragma once
#include "Action.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>
class ActionBinder
{
	using KeyMap = std::unordered_map<sf::Keyboard::Scancode, ActionID>;
private:
	KeyMap m_keyMap;
	ActionBinder() {
		// Initial keyboard Binding
		m_keyMap[sf::Keyboard::Scancode::W] = ActionID::characterMoveUp;
		m_keyMap[sf::Keyboard::Scancode::A] = ActionID::characterMoveLeft;
		m_keyMap[sf::Keyboard::Scancode::S] = ActionID::characterMoveDown;
		m_keyMap[sf::Keyboard::Scancode::D] = ActionID::characterMoveRight;
		m_keyMap[sf::Keyboard::Scancode::Space] = ActionID::characterJump;
		//

	}
	~ActionBinder() = default;
	ActionBinder(ActionBinder&) = delete;
	ActionBinder(ActionBinder&&) = delete;
	ActionBinder& operator=(ActionBinder&) = delete;
	ActionBinder& operator=(ActionBinder&&) = delete;

public:
	static Action getAction(sf::Event event) {
		static ActionBinder binder;
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			return Action{ binder.m_keyMap[event.key.scancode], {true, 0, 0} };
			break;
		case sf::Event::KeyReleased:
			return Action{ binder.m_keyMap[event.key.scancode], {false, 0, 0} };
			break;
		case sf::Event::MouseButtonPressed:
			return Action{ ActionID::mousePrimary , {true, event.mouseButton.x, event.mouseButton.x} };
			break;
		case sf::Event::MouseButtonReleased:
			return Action{ ActionID::mousePrimary , {false, event.mouseButton.x, event.mouseButton.x} };
			break;
		case sf::Event::MouseMoved:

			break;
		case sf::Event::MouseWheelScrolled:
			break;
		default:
			break;

		}

		return Action{ ActionID::cameraMoveDown, {false, 0, 0} };
	}
private:

};

