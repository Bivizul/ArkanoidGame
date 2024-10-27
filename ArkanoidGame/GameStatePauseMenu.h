#pragma once
#include "GameStateData.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Game;

	class GameStatePauseMenuData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
	};
}
