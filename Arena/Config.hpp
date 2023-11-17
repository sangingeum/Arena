#pragma once
#include <SFML/Graphics.hpp>

// Singleton config
// It stores configuration related values and some constants
class Config
{
	Config()
	{
		changeResolution(1280, 720);
		if (!font.loadFromFile("asset/font/PlaypenSans-Medium.ttf"))
			throw std::runtime_error("Failed to load font file: font/PlaypenSans-Medium.ttf");
		font.setSmooth(true);
	}
	Config(const Config&) = delete;
	void operator=(const Config&) = delete;
	~Config() = default;
public:

	static Config& instance() {
		static Config config;
		return config;
	}
	void changeResolution(unsigned windowWidth_, unsigned windowHeight_) {
		windowWidth = windowWidth_;
		windowHeight = windowHeight_;
		halfWindowWidth = windowWidth / 2.f;
		halfWindowHeight = windowHeight / 2.f;
	}

	sf::Font font;
	uint32_t frameRate{ 60 };
	unsigned windowWidth{ 1280 };
	unsigned windowHeight{ 720 };
	float halfWindowWidth;
	float halfWindowHeight;
	float deltaTime{ 1 / 60.f };
	uint32_t velocityIterations{ 16 };
	uint32_t positionIterations{ 6 };
	const float pi{ 3.14159265358979323846f };
	const float radianToDegree{ 57.2958f };
	sf::String windowName{ "Arena" };
};

