#pragma once
#include "Ball.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		void Init(float x, float y);
		bool CheckCollisionWithBall(const Ball& ball);
	};
}
