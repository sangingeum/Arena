#pragma once
#include <SFML/Graphics.hpp>

// Singleton config
class Config
{
	Config() {}
	Config(const Config&) = delete;
	void operator=(const Config&) = delete;
	~Config() = default;
public:

	static Config& instance() {
		static Config config;
		return config;
	}
	unsigned frameRate{ 60 };
	int windowWidth{ 1200 };
	int widowHeight{ 700 };
	const float pi{ 3.14159265358979323846f };
	sf::String windowName{ "Arena" };
};

