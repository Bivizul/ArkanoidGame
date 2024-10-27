#include "GameSettings.h"
#include "LevelLoader.h"
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>

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

	void LevelLoader::LoadLevelsFromFile() 
	{
		std::string filepath = SETTINGS.LEVELS_CONFIG_PATH;
		std::string line;
		std::ifstream file(filepath);
		int y = 0;
		int levelCounter = 0;

		if (!file.is_open()) {
			std::cerr << "Error: Cannot open level config file at " << filepath << std::endl;
			return;
		}

		while (getline(file, line)) 
		{
			if (line.rfind("level ", 0) == 0) 
			{
				auto level = std::stoi(line.substr(6, line.size() - 6));
				std::cout << "Loading level " << level << std::endl;
				levels.emplace_back(Level());
				++levelCounter;
				y = 0;
			}
			else {
				int x = 0;
				for (char c : line) 
				{
					if (c != ' ') 
					{
						levels.back().m_blocks.emplace_back(std::make_pair(sf::Vector2i{ x, y }, CharToBlockType(c)));
					}
					++x;
				}
			}
			++y;
		}

		std::cout << "Total levels loaded: " << levelCounter << std::endl;
		file.close();
	}

	int LevelLoader::GetLevelCount()
	{
		return levels.size();
	}
}