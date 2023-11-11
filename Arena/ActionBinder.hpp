#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

class ActionBinder
{
	using KeyMap = std::unordered_map<sf::Keyboard::Scancode, ActionID>;
private:
	KeyMap m_keyMap;
	ActionBinder();
	~ActionBinder() = default;
	ActionBinder(ActionBinder&) = delete;
	ActionBinder& operator=(ActionBinder&) = delete;

public:
	static Action getAction(sf::Event event);
};

