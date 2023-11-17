#include "ActionBinder.hpp"

ActionBinder::ActionBinder() {
	// Initial Keyboard Binding
	// Character movements
	m_keyMap[sf::Keyboard::Scancode::W] = ActionID::characterMoveUp;
	m_keyMap[sf::Keyboard::Scancode::A] = ActionID::characterMoveLeft;
	m_keyMap[sf::Keyboard::Scancode::S] = ActionID::characterMoveDown;
	m_keyMap[sf::Keyboard::Scancode::D] = ActionID::characterMoveRight;
	m_keyMap[sf::Keyboard::Scancode::Space] = ActionID::characterJump;
	m_keyMap[sf::Keyboard::Scancode::Z] = ActionID::characterAttack1;
	m_keyMap[sf::Keyboard::Scancode::X] = ActionID::characterAttack2;
	m_keyMap[sf::Keyboard::Scancode::C] = ActionID::characterAttack3;
	// Camera
	m_keyMap[sf::Keyboard::Scancode::Q] = ActionID::cameraMoveLeft;
	m_keyMap[sf::Keyboard::Scancode::E] = ActionID::cameraMoveRight;
	// Number
	m_keyMap[sf::Keyboard::Scancode::Num1] = ActionID::number1;
	m_keyMap[sf::Keyboard::Scancode::Num2] = ActionID::number2;
	m_keyMap[sf::Keyboard::Scancode::Num3] = ActionID::number3;
	m_keyMap[sf::Keyboard::Scancode::Num4] = ActionID::number4;
	m_keyMap[sf::Keyboard::Scancode::Num5] = ActionID::number5;
	// Game
	m_keyMap[sf::Keyboard::Scancode::P] = ActionID::pause;
	// Special keys
	m_keyMap[sf::Keyboard::Scancode::LShift] = ActionID::leftShift;
}

Action ActionBinder::getAction(sf::Event event) {
	static ActionBinder binder;
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		return Action{ binder.m_keyMap[event.key.scancode],{ true, 0.f, 0.f } };
		break;
	case sf::Event::KeyReleased:
		return Action{ binder.m_keyMap[event.key.scancode],{ false, 0.f, 0.f } };
		break;
	case sf::Event::MouseButtonPressed:
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
			return Action{ ActionID::mousePrimary ,{ true, static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) } };
			break;
		case sf::Mouse::Button::Right:
			return Action{ ActionID::mouseSecondary ,{ true, static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) } };
			break;
		}
		break;
	case sf::Event::MouseButtonReleased:
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
			return Action{ ActionID::mousePrimary ,{ false, static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) } };
			break;
		case sf::Mouse::Button::Right:
			return Action{ ActionID::mouseSecondary ,{ false, static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) } };
			break;
		}
		break;
	case sf::Event::MouseMoved:
		return Action{ ActionID::mouseMove ,{ true, static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) } };

		break;
	case sf::Event::MouseWheelScrolled:
	{
		float zoom = 1.f;
		if (std::abs(event.mouseWheelScroll.delta) <= 10) {
			zoom -= ((int)event.mouseWheelScroll.delta) / 50.f;
		}
		return Action{ ActionID::cameraZoom ,{ true, zoom, 0.f } };
		break;
	}
	case sf::Event::Closed:
		return Action{ ActionID::windowClose,{ false, 0.f, 0.f } };
		break;
	default:
		return Action{ ActionID::noAction,{ false, 0.f, 0.f } };
		break;
	}
	return Action{ ActionID::noAction,{ false, 0.f, 0.f } };
}
