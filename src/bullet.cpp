#include "bullet.h"

Bullet::Bullet(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 64, 128)
    , m_step(1.f)
    , m_angle(0.f)
    , m_tileWidth(64)
    , m_tileHeight(64)
    , m_engaged(false)
    , m_deleteMe(false)
    , m_deleteTimeAccumulator(0.f)
{
    m_eyes = new Eyes("resources/sprites/darkness_eyes.png");

    Animation animation("bullet", m_tileWidth, m_tileHeight);
    animation.addFrames(x, x, y, 1.f);
    addAnimation(animation, sf::seconds(1.f));

    animation = Animation("engaged", m_tileWidth, m_tileHeight);
    animation.addFrames(x, x, 1, 1.f);
    addAnimation(animation, sf::seconds(1.f));

    play("bullet");
}

Bullet::~Bullet()
{
}

void Bullet::run(float angle)
{
    m_angle = angle;
}

void Bullet::engage(sf::Vector2f pos)
{
    m_engaged = true;
    play("engaged");

    setPosition(pos);
    m_eyes->setPosition(pos + sf::Vector2f(14, 16));
}

bool Bullet::engaged()
{
    return m_engaged;
}

bool Bullet::deleteMe()
{
    return m_deleteMe;
}

void Bullet::update(sf::Time delta)
{
    if (!m_engaged) {
        float newX = cos(m_angle) * m_step;
        float newY = sin(m_angle) * m_step;

        move(newX, newY);
    } else {
        m_eyes->update(delta);

        m_deleteTimeAccumulator += delta.asSeconds();

        if (m_deleteTimeAccumulator >= 6) {
            m_eyes->die();
        }

        if (m_deleteTimeAccumulator >= 8) {
            m_deleteMe = true;

            m_deleteTimeAccumulator = 0.f;
        }
    }

    AnimatedSprite::update(delta);

}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    AnimatedSprite::draw(target, states);

    if (m_engaged)
        target.draw(*m_eyes);
}
