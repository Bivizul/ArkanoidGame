#pragma once
#include "Block.h"
#include "ThreeHitBlock.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ArkanoidGame 
{
	enum class BlockType
	{
		Simple,
		ThreeHit,
		Unbreackable
	};

	struct Level {
		std::vector<std::pair<sf::Vector2i, BlockType>> m_blocks;
	};

	class LevelLoader final
	{
	public:
		LevelLoader() { LoadLevelsFromFile(); };
		Level& GetLevel(int i);
		~LevelLoader() = default;
		int GetLevelCount();
	private:
		void LoadLevelsFromFile();

		static BlockType CharToBlockType(char symbol);
		std::vector<Level> levels;
	};

}
