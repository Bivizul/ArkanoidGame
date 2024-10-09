#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Game;

	class GameStateGameOverData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		void SetWin(bool win);

	private:
		// Resources
		sf::Font font;

		float timeSinceGameOver = 0.f;

		// UI data
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

		std::vector<sf::Text> menuOptions;
		int selectedOptionIndex = 0;
		bool isWin = false;
	};
}
