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
		// Character movements
		m_keyMap[sf::Keyboard::Scancode::W] = ActionID::characterMoveUp;
		m_keyMap[sf::Keyboard::Scancode::A] = ActionID::characterMoveLeft;
		m_keyMap[sf::Keyboard::Scancode::S] = ActionID::characterMoveDown;
		m_keyMap[sf::Keyboard::Scancode::D] = ActionID::characterMoveRight;
		m_keyMap[sf::Keyboard::Scancode::Space] = ActionID::characterJump;
		// Camera
		m_keyMap[sf::Keyboard::Scancode::Q] = ActionID::cameraMoveLeft;
		m_keyMap[sf::Keyboard::Scancode::E] = ActionID::cameraMoveRight;
		// Number
		m_keyMap[sf::Keyboard::Scancode::Num1] = ActionID::number1;
		m_keyMap[sf::Keyboard::Scancode::Num2] = ActionID::number2;
		m_keyMap[sf::Keyboard::Scancode::Num3] = ActionID::number3;
		m_keyMap[sf::Keyboard::Scancode::Num4] = ActionID::number4;
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
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Button::Left:
				return Action{ ActionID::mousePrimary , {true, event.mouseButton.x, event.mouseButton.y} };
				break;
			case sf::Mouse::Button::Right:
				return Action{ ActionID::mouseSecondary , {true, event.mouseButton.x, event.mouseButton.y} };
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Button::Left:
				return Action{ ActionID::mousePrimary , {false, event.mouseButton.x, event.mouseButton.y} };
				break;
			case sf::Mouse::Button::Right:
				return Action{ ActionID::mouseSecondary , {false, event.mouseButton.x, event.mouseButton.y} };
				break;
			}
			break;
		case sf::Event::MouseMoved:
			return Action{ ActionID::mouseMove , {true, event.mouseButton.x, event.mouseButton.x} };
			break;
		case sf::Event::MouseWheelScrolled:
		{
			float zoom = 1.f;
			if (std::abs(event.mouseWheelScroll.delta) <= 10) {
				zoom -= ((int)event.mouseWheelScroll.delta) / 50.f;
			}
			return Action{ ActionID::cameraZoom , {true, zoom, 0} };
			break;
		}
		case sf::Event::Closed:
			return Action{ ActionID::windowClose, {false, 0, 0} };
			break;
		default:
			return Action{ ActionID::noAction, {false, 0, 0} };
			break;
		}
	}
};

