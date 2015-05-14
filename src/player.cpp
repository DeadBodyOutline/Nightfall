#include "player.h"

Player::Player(const std::string &fileName, int x, int y)
    : Character(fileName, x, y)
    , m_weaponDecay(1.f)
    , m_maxNumBullets(10) // TODO 10
    , m_numBullets(m_maxNumBullets)
    , m_timeToIncBullet(2.f)
    , m_timeAccumulator(0.f)
{
    m_bulletIndicator = new Sprite("resources/sprites/bullet_indicator.png");
    m_step = 0.1f;
}

Player::~Player()
{
}

void Player::shoot(int x, int y)
{
    if (m_numBullets <= 0)
        return;

    --m_numBullets;

    Character::shoot(x, y);
}
void Player::setWeaponDecay(float decay)
{
    // TODO will set the weapong recharge value, near the reactor, recovers fast
    m_weaponDecay = decay;
}

void Player::update(sf::Time delta)
{
    m_timeAccumulator += delta.asSeconds() * (1.f / m_weaponDecay);
    if (m_timeAccumulator >= m_timeToIncBullet) {
        if (m_numBullets < m_maxNumBullets)
            ++m_numBullets;

        m_timeAccumulator = 0.f;
    }

    Character::update(delta);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_visible)
        return;

    int x = position().x - 16;
    int y = position().y - 8;

    int i;
    for (i = 0; i < m_numBullets; i++) {
        m_bulletIndicator->setPosition(x, y);
        target.draw(*m_bulletIndicator);

        x += 1 + m_bulletIndicator->width();
    }

    Character::draw(target, states);
}
