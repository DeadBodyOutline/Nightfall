#include "character.h"

Character::Character(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 288, 256)
    , m_collidingEnabled(true)
    , m_tileWidth(32)
    , m_tileHeight(32)
{
    Animation animation("steady", m_tileWidth, m_tileHeight);
    animation.addFrames(x, x, y, 1.f);

    addAnimation(animation, sf::seconds(1.f));
    play("steady");
}

Character::~Character()
{
}

void Character::setColliding(bool colliding)
{
    m_collidingEnabled = colliding;
}

bool Character::colliding()
{
    return m_collidingEnabled;
}

void Character::setPosition(int x, int y)
{
    sf::Vector2f v(x, y);
    this->setPosition(v);
}

void Character::setPosition(sf::Vector2f point)
{
    if (point == Sprite::position())
        return;

    AnimatedSprite::setPosition(point.x, point.y);
}

void Character::update(sf::Time delta)
{
    AnimatedSprite::update(delta);
}

bool Character::collideWith(Sprite *sprite)
{
    if (!m_collidingEnabled)
        return false;

    return Sprite::collideWith(sprite);
}
