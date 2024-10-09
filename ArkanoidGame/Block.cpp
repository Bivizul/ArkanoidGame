#include "Ball.h"
#include "Block.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	void Block::Init(float x, float y)
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(sprite, BLOCK_WIDTH, BLOCK_HEIGHT, texture);
		sprite.setPosition({ x, y });
	}

	bool Block::CheckCollisionWithBall(const Ball& ball)
	{
		auto sqr = [](float x) {
			return x * x;
			};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball.GetPosition();
		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}
}