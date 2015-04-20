#include "reactor.h"

Reactor::Reactor(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 64, 96)
    , m_energyLevel(100)
    , m_tileWidth(64)
    , m_tileHeight(96)
{
    m_energyIndicator = new Sprite("resources/sprites/energy_indicator.png");

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

void Reactor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_visible)
        return;

    int x = position().x - 16;
    int y = position().y + 8;

    int i;
    for (i = 0; i < m_energyLevel / 2; i++) {
        m_energyIndicator->setPosition(x, y);
        target.draw(*m_energyIndicator);

        x += m_energyIndicator->width();
    }

    AnimatedSprite::draw(target, states);
}
