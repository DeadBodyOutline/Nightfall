#include "character.h"

Character::Character(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 288, 256)
    , m_collidingEnabled(true)
    , m_tileWidth(32)
    , m_tileHeight(32)
    , m_xOffset(0)
    , m_yOffset(2)
    , m_xDirection(1)
    , m_yDirection(1)
{
    Animation animation("steady", m_tileWidth, m_tileHeight);
    animation.addFrames(x, x, y, 1.f);

    addAnimation(animation, sf::seconds(1.f));
    play("steady");
}

Character::~Character()
{
}

void Character::shoot(int x, int y)
{
    std::cout << "I am shooting at (" << x << ", " << y << ")!" << std::endl;
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

    updatePos(point);
}

void Character::setDirection(int x, int y)
{
    if (x == m_xDirection)
        return;

    m_xDirection = x;
    m_yDirection = y;

    m_sprite.setScale(m_xDirection, m_yDirection);

    // force position update
    updatePos(m_sprite.getPosition());
    // TODO FUUUUU
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

void Character::updatePos(sf::Vector2f point)
{
    //sf::IntRect r = m_sprite.getTextureRect();

    //m_sprite.setTextureRect(sf::IntRect(r.width, 0, -r.width, r.height));
    //float newX = point.x;
    //float newY = point.y;
    float newX = point.x + (m_xDirection == -1 ? m_tileWidth : 0);
    float newY = point.y - (m_yDirection == -1 ? m_tileHeight : 0);
    //float newX = point.x + m_xOffset + (m_xDirection == -1 ? m_tileWidth : 0);
    //float newY = point.y - m_yOffset + (m_yDirection == -1 ? m_tileHeight : 0);

    AnimatedSprite::setPosition(newX, newY);
}
