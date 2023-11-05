#pragma once
#include <SFML/Graphics.hpp>

// Singleton config
// It stores configuration related values and some constants
class Config
{
	Config()
		:halfWindowWidth(windowWidth / 2.f), halfWindowHeight(widowHeight / 2.f)
	{}
	Config(const Config&) = delete;
	void operator=(const Config&) = delete;
	~Config() = default;
public:

	static Config& instance() {
		static Config config;
		return config;
	}
	uint32_t frameRate{ 60 };
	int windowWidth{ 1280 };
	int widowHeight{ 720 };
	float halfWindowWidth;
	float halfWindowHeight;
	int32 velocityIterations{ 16 };
	int32 positionIterations{ 6 };
	const float pi{ 3.14159265358979323846f };
	const float screenToWorldRatio{ 0.01f };
	const float radianToDegree{ 57.2958f };
	sf::String windowName{ "Arena" };
};

