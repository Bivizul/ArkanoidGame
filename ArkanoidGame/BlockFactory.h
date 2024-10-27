#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace ArkanoidGame
{
	class Block;

	class BlockFactory
	{
	protected:
		int createdBreackableBlocksCount = 0;
	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
		virtual ~BlockFactory() = default;
		int GetcreatedBreackableBlocksCount();
		void ClearCounter();
	};

	class UnbreackableBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		~UnbreackableBlockFactory() override = default;
	};

	class SimpleBlockFactory final : public BlockFactory 
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		~SimpleBlockFactory() override = default;

	};

	class DoubleHitBlockFactory final : public BlockFactory 
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		~DoubleHitBlockFactory() override = default;

	};

	class ThreeHitBlockFactory final : public BlockFactory 
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		~ThreeHitBlockFactory() override = default;

	};
}