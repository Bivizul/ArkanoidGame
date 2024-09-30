#include "Ball.h"
#include "Block.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>

namespace
{
	// id textures
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	void Block::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(sprite, BLOCK_WIDTH, BLOCK_HEIGHT, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f });

		const float angle = 45.f + rand() % 90; // [45, 135] degree
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Block::Update(float timeDelta)
	{
		/*const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x <= 0 || pos.x >= SCREEN_WIDTH) {
			direction.x *= -1;
		}

		if (pos.y <= 0 || pos.y >= SCREEN_HEIGHT) {
			direction.y *= -1;
		}*/
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