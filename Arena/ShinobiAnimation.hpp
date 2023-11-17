#pragma once
#include "Component.hpp"
#include "AssetManager.hpp"
#include "CharacterData.hpp"

class ShinobiAnimation
{
public:
	static CAnimation getIdle() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Idle), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 6, 3.f };
	}
	static CAnimation getJump() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Jump), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 12, 1.5f };
	}
};

