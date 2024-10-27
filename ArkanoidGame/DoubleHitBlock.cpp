#include "GameSettings.h"
#include "DoubleHitBlock.h"

namespace ArkanoidGame
{
    DoubleHitBlock::DoubleHitBlock(const sf::Vector2f& position)
        : SmoothDestroyableBlock(position, sf::Color::Red)
    {
        hitCount = 2;
    }

    void DoubleHitBlock::OnHit() 
    {
        --hitCount;
        StageChange();

        if (hitCount == 0) {
            hitCount = 1;
            StartTimer(SETTINGS.BREAK_DELAY);
        }
    }

    void DoubleHitBlock::StageChange()
    {
        if (hitCount < 2)
        {
            sprite.setColor(sf::Color::Green);
            color = sf::Color::Green;
        }
    }
}