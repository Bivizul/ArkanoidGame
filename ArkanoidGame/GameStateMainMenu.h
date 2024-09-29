#pragma once
#include "Menu.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class GameStateMainMenuData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;
		Menu menu;
	};
}
