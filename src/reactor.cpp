#include "reactor.h"

Reactor::Reactor(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 64, 96)
    , m_energyLevel(100)
    , m_tileWidth(64)
    , m_tileHeight(96)
{
    Animation animation("steady", m_tileWidth, m_tileHeight);
    animation.addFrames(x, x, y, 1.f);

    addAnimation(animation, sf::seconds(1.f));
    play("steady");
}

Reactor::~Reactor()
{
}

int Reactor::energyLevel()
{
    return m_energyLevel;
}

void Reactor::update(sf::Time delta)
{
    AnimatedSprite::update(delta);
}
