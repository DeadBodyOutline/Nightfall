#include "character.h"

Character::Character(const std::string &fileName, int x, int y)
    : AnimatedSprite(fileName, 32, 2304)
    , m_xDirection(1)
    , m_yDirection(1)
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

void Character::shoot(int x, int y)
{
    sf::Vector2f posCorrection = sf::Vector2f(32, 16); // XXX I don't know why, but will discover someday

    Bullet *bullet = new Bullet("resources/sprites/darkbullet.png");

    sf::Vector2f v = sf::Vector2f(x - 32, y - 32) - (position() - posCorrection);
    float angle = atan2f(v.y, v.x);

    bullet->run(angle);
    bullet->setPosition(position() - posCorrection);

    m_bullets.push_back(bullet);
}

std::vector<Bullet *> Character::bullets()
{
    return m_bullets;
}

void Character::destroyBullet(Bullet *bullet)
{
    m_bullets.erase(std::remove(m_bullets.begin(), m_bullets.end(), bullet), m_bullets.end());
    delete bullet;
}

sf::FloatRect Character::boundingBox()
{
    // XXX seems to do nothing oO
    return sf::FloatRect(position().x, position().y, m_tileWidth, m_tileHeight);
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

    // shit fucking shit
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, 0);
    m_sprite.setScale(m_xDirection, m_yDirection);
}

int Character::directionX()
{
    return m_xDirection;
}

void Character::update(sf::Time delta)
{
    // XXX use "contains" or something like that
    for (auto bullet : m_bullets) {
        if (bullet->position().x + 32 < 0 || bullet->position().y + 32 < 0  ||
                bullet->position().x > 800 || bullet->position().y > 608)
            destroyBullet(bullet);
        else
            bullet->update(delta);
    }

    AnimatedSprite::update(delta);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_visible)
        return;

    for (auto bullet : m_bullets)
        target.draw(*bullet, states);

    AnimatedSprite::draw(target, states);
}

bool Character::collideWith(Sprite *sprite)
{
    if (!m_collidingEnabled)
        return false;

    return Sprite::collideWith(sprite);
}

void Character::updatePos(sf::Vector2f point)
{
    float newX = point.x - m_tileWidth / 2;
    float newY = point.y;

    AnimatedSprite::setPosition(newX, newY);
}
