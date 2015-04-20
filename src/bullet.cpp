#include "bullet.h"

Bullet::Bullet(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 64, 128)
    , m_step(1.f)
    , m_angle(0.f)
    , m_tileWidth(64)
    , m_tileHeight(64)
    , m_engaged(false)
{
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

void Bullet::engage()
{
    // TODO stick here
    m_engaged = true;
    play("engaged");
}

void Bullet::update(sf::Time delta)
{
    if (!m_engaged) {
        float newX = cos(m_angle) * m_step;
        float newY = sin(m_angle) * m_step;

        move(newX, newY);
    }

    AnimatedSprite::update(delta);
}
