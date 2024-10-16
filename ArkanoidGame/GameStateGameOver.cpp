#include "Application.h"
#include "Game.h"
#include "GameStateGameOver.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	const char* PLAYER_NAME = "Player";

	void GameStateGameOverData::Init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameOver = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200; // a means Alfa, opacity
		background.setFillColor(backgroundColor);

		Game& game = Application::Instance().GetGame();
		isWin = game.GetIsWin();

		if (isWin)
		{
			gameOverText.setFont(font);
			gameOverText.setCharacterSize(48);
			gameOverText.setStyle(sf::Text::Bold);
			gameOverText.setFillColor(sf::Color::Green);
			gameOverText.setString("WIN");

			sf::Text playAgain;
			playAgain.setFont(font);
			playAgain.setCharacterSize(36);
			playAgain.setString("Play again");
			playAgain.setFillColor(sf::Color::White);
			menuOptions.push_back(playAgain);

			sf::Text exitToMenu;
			exitToMenu.setFont(font);
			exitToMenu.setCharacterSize(36);
			exitToMenu.setString("Exit to menu");
			menuOptions.push_back(exitToMenu);

			menuOptions[selectedOptionIndex].setFillColor(sf::Color::Yellow);
		}
		else
		{
			gameOverText.setFont(font);
			gameOverText.setCharacterSize(48);
			gameOverText.setStyle(sf::Text::Bold);
			gameOverText.setFillColor(sf::Color::Red);
			gameOverText.setString("GAME OVER");
		}

		recordsTableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::multimap<int, std::string> sortedRecordsTable;
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isPlayerInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) // Note, we can do several actions in for action block
		{
			recordsTableTexts.emplace_back();
			sf::Text& text = recordsTableTexts.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setCharacterSize(24);
			if (it->second == PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isPlayerInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		if (!isPlayerInTable)
		{
			sf::Text& text = recordsTableTexts.back();
			std::stringstream sstream;
			int playerScores = game.GetRecordByPlayerId(PLAYER_NAME);
			sstream << MAX_RECORDS_TABLE_SIZE << ". " << PLAYER_NAME << ": " << playerScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Press Space to restart\nEsc to exit to main menu");
	}

	void GameStateGameOverData::HandleWindowEvent(const sf::Event& event)
	{
		if (isWin)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);
					selectedOptionIndex = (selectedOptionIndex - 1 + (int)menuOptions.size()) % (int)menuOptions.size();
					menuOptions[selectedOptionIndex].setFillColor(sf::Color::Yellow);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);
					selectedOptionIndex = (selectedOptionIndex + 1) % menuOptions.size();
					menuOptions[selectedOptionIndex].setFillColor(sf::Color::Yellow);
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (selectedOptionIndex == 0)
					{
						Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
					}
					else if (selectedOptionIndex == 1)
					{
						Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
					}
				}
			}
		}
		else
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
				}
			}
		}
	}

	void GameStateGameOverData::Update(float timeDelta)
	{
		timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		gameOverText.setFillColor(gameOverTextColor);

	}

	void GameStateGameOverData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);

		gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 1.f }));
		gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(gameOverText);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(recordsTableTexts.size());
		for (auto& text : recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		if (isWin)
		{
			for (size_t i = 0; i < menuOptions.size(); ++i)
			{
				sf::Text& option = menuOptions[i];
				option.setOrigin(GetTextOrigin(option, { 0.5f, 0.5f }));
				option.setPosition(viewSize.x / 2.f, viewSize.y - 100.f + i * 50.f);
				window.draw(option);
			}
		}
		else
		{
			hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 1.f }));
			hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
			window.draw(hintText);
		}
	}

	void GameStateGameOverData::SetWin(bool win)
	{
		isWin = win;
	}
}
