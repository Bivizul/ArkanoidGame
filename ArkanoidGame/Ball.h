#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);

		void ReboundFromPlatform();

	private:
		sf::Vector2f direction;
	};
}


