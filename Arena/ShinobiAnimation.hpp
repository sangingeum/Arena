#pragma once
#include "Component.hpp"
#include "AssetManager.hpp"
#include "CharacterData.hpp"

class ShinobiAnimation
{
public:
	static CAnimation getAttack_1() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Attack_1), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 5, 3.f };
	}
	static CAnimation getAttack_2() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Attack_2), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 3, 3.f };
	}
	static CAnimation getAttack_3() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Attack_3), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 4, 3.f };
	}
	static CAnimation getDead() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Dead), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 4, 1.5f };
	}
	static CAnimation getHurt() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Hurt), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 2, 1.5f };
	}
	static CAnimation getIdle() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Idle), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 6, 3.f };
	}
	static CAnimation getJump() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Jump), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 12, 1.0f };
	}
	static CAnimation getRun() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Run), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 8, 0.7f };
	}
	static CAnimation getShield() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Shield), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 4, 1.5f };
	}
	static CAnimation getWalk() {
		constexpr float halfWidth = CharacterData::getShinobiHalfWidth();
		constexpr float halfHeight = CharacterData::getShinobiHalfHeight();
		return CAnimation{ AssetManager::getTexture(TextureID::Shinobi_Walk), sf::IntRect{ 0, 0, 128, 128 }, sf::Vector2f{ halfWidth * 2.f, halfHeight * 2.f }, 8, 1.5f };
	}

};

