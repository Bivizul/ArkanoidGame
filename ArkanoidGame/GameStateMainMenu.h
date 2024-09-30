#pragma once
#include "Menu.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class GameStateMainMenuData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		sf::Font font;
		Menu menu;
	};
}
