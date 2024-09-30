#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);

		bool CheckCollisionWithBall(const Ball& ball);

	private:
		sf::Vector2f direction;
	};
}
