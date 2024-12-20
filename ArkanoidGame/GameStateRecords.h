#pragma once
#include "GameStateData.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace ArkanoidGame
{
	class Game;

	class GameStateRecordsData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		// Resources
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};
}
