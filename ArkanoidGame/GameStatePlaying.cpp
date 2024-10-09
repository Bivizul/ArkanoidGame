#include "Application.h"
#include "Game.h"
#include "GameStatePlaying.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "GameStateGameOver.h"

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		platform.Init();
		ball.Init();

		float x = BLOCK_WIDTH / 2;
		blocks.reserve(13);
		for (size_t i = 0; i < 13; i++)
		{
			Block block;
			blocks.push_back(block);
			blocks[i].Init(x, 50 + BLOCK_HEIGHT / 2);
			x += BLOCK_WIDTH;
		}

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		platform.Update(timeDelta);
		ball.Update(timeDelta);

		for (auto it = blocks.begin(); it != blocks.end(); )
		{
			if (it->CheckCollisionWithBall(ball)) {
				ball.ReboundFromBlock();
				it = blocks.erase(it);
			}
			else {
				++it;
			}
		}

		const bool isCollision = platform.CheckCollisionWithBall(ball);
		if (isCollision) {
			ball.ReboundFromPlatform();
		}

		const bool isWin = blocks.size() == 0;
		const bool isLoss = (!isCollision && ball.GetPosition().y > platform.GetRect().top);
		if (isWin || isLoss)
		{
			gameOverSound.play();
			Game& game = Application::Instance().GetGame();
			game.SetIsWin(isWin);
			game.PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game objects
		platform.Draw(window);
		ball.Draw(window);

		for (Block& block : blocks)
		{
			block.Draw(window);
		}

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
