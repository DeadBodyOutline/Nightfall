#include "enemy.h"

Enemy::Enemy(const std::string &fileName, int x, int y)
    : Character(fileName, x, y)
    , m_currentTarget(0)
    , m_reactorHit(false)
    , m_freeze(false)
    , m_deleteMe(false)
    , m_deleteTimeAccumulator(0.f)
{
    m_step = 0.05f;
}

Enemy::~Enemy()
{
}

void Enemy::shoot(int x, int y)
{
    Character::shoot(x, y);
}

// enemy only function, track target
void Enemy::setTarget(std::vector<sf::Vector2f> waypoints, sf::Vector2f end)
{
    m_target = waypoints;
    m_target.push_back(end);
}

bool Enemy::reactorHit()
{
    return m_reactorHit;
}

void Enemy::freeze()
{
    m_freeze = true;
    // TODO freeze state
}

bool Enemy::deleteMe()
{
    return m_deleteMe;
}

void Enemy::update(sf::Time delta)
{
    if (m_freeze) {
        m_deleteTimeAccumulator += delta.asSeconds();

        if (m_deleteTimeAccumulator >= 8) {
            m_deleteMe = true;

            m_deleteTimeAccumulator = 0.f;
        }

        for (auto bullet : m_bullets)
            bullet->update(delta);

        Character::update(delta);
        return;
    }

    float x = (m_xDirection == 1 ? 0 : 32);
    int diff = 2;

    if (m_currentTarget == (int)m_target.size() -1) {
        if (m_xDirection == -1)
            diff = 96;
        else
            diff = 32;
    }

    if (fabs(x + position().x - m_target[m_currentTarget].x) <= 2 + x + diff) {
        m_currentTarget++;

        if (m_currentTarget >= (int)m_target.size())
            m_reactorHit = true;
    }

    if (!m_reactorHit) {
        sf::Vector2f posCorrection = sf::Vector2f(0, 0); // damn
        if (m_currentTarget == (int)m_target.size() -1)
            posCorrection = sf::Vector2f(m_xDirection == 1 ? 32 : 96, 48);

        sf::Vector2f v = sf::Vector2f(
                m_target[m_currentTarget].x, m_target[m_currentTarget].y)
                + posCorrection - position();

        float angle = atan2f(v.y, v.x);

        float newX = cos(angle) * m_step;
        float newY = sin(angle) * m_step;

        move(newX, newY);
    }

    Character::update(delta);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_freeze) {
        for (auto bullet : m_bullets)
            target.draw(*bullet, states);

        return;
    }

    if (!m_visible)
        return;

    Character::draw(target, states);
}
