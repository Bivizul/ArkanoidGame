#pragma once
#include "Block.h"

namespace ArkanoidGame
{
    class DoubleHitBlock : public SmoothDestroyableBlock 
    {
    public:
        DoubleHitBlock(const sf::Vector2f& position);

    private:
        void OnHit() override;
        void StageChange();
    };
}
