#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Game;

	class GameStateGameWinData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		// Resources
		sf::Font font;

		float timeSinceGameWin = 0.f;

		// UI data
		sf::RectangleShape background;
		sf::Text gameWinText;
		sf::Text hintText;
	};
}
