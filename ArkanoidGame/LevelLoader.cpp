#include "GameSettings.h"
#include "LevelLoader.h"
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "DoubleHitBlock.h"

namespace ArkanoidGame {
	Level& LevelLoader::GetLevel(int i) 
	{
		std::cout << "Requested level index: " << i << ", total levels: " << levels.size() << std::endl;

		if (i < 0 || i >= levels.size()) 
		{
			std::cerr << "Error: Invalid level index: " << i << std::endl;
			throw std::out_of_range("Invalid level index: " + std::to_string(i));
		}
		return levels.at(i);
	}

	BlockType LevelLoader::CharToBlockType(char symbol) 
	{
		BlockType blockType;
		switch (symbol)
		{
		case '1':
			blockType = BlockType::Simple;
			break;
		case '2':
			blockType = BlockType::DoubleHit;
			break;
		case '3':
			blockType = BlockType::ThreeHit;
			break;
		case '0':
			blockType = BlockType::Unbreackable;
			break;
		default:
			assert(false);
			break;
		}
		return blockType;
	}

	void LevelLoader::LoadLevelsFromFile() {
		std::string filepath = SETTINGS.LEVELS_CONFIG_PATH;
		std::ifstream file(filepath);
		std::string line;
		int y = 0;

		while (getline(file, line)) {
			if (line.rfind("level ", 0) == 0) {
				levels.emplace_back(Level());
				y = 0;
			}
			else {
				int x = 0;
				for (char c : line) {
					if (c != ' ') {
						BlockType blockType;
						if (c == '1') {
							blockType = BlockType::Simple;
						}
						else if (c == '2') {
							blockType = BlockType::DoubleHit;
						}
						else if (c == '3') {
							blockType = BlockType::ThreeHit;
						}
						else {
							blockType = BlockType::Unbreackable;
						}

						levels.back().m_blocks.emplace_back(std::make_pair(sf::Vector2i{ x, y }, blockType));
					}
					++x;
				}
			}
			++y;
		}

		file.close();
	}

	int LevelLoader::GetLevelCount()
	{
		return (int)levels.size();
	}
}