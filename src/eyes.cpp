#include "eyes.h"

Eyes::Eyes(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 32, 128)
    , m_tileWidth(32)
    , m_tileHeight(32)
{
    Animation animation("scary", m_tileWidth, m_tileHeight);
    animation.addFramesY(x, 0, 2, 2.f);
    addAnimation(animation, sf::seconds(2.f));

    animation = Animation("dead", m_tileWidth, m_tileHeight);
    animation.addFramesY(x, 3, 3, 1.f);
    addAnimation(animation, sf::seconds(1.f));

    play("scary");
}

Eyes::~Eyes()
{
}

void Eyes::die()
{
    play("dead");
}
