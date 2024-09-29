#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Ball;

	class Platform : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);
		
		bool CheckCollisionWithBall(const Ball& ball);

	private:
		void Move(float speed);
	};
}


