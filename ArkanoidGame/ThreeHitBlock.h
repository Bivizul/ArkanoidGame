#pragma once
#include "Block.h"
#include "Collidable.h"
#include <memory>

namespace ArkanoidGame {
	class ThreeHitBlock : public SmoothDestroyableBlock
	{
	public:
		ThreeHitBlock(const sf::Vector2f& position);

	private:
		void OnHit() override;
		void StageChange();
	};
}

