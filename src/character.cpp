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
    sf::Vector2f posCorrection = sf::Vector2f(48, 16); // XXX I don't know why, but will discover someday

    Bullet *bullet = new Bullet("resources/sprites/darkbullet.png");

    sf::Vector2f v = sf::Vector2f(x - 32, y - 32) - (position() - posCorrection);
    float angle = atan2f(v.y, v.x);

    bullet->run(angle);
    bullet->setPosition(position() - posCorrection);

    m_bullets.push_back(bullet);
}
void Character::setWeaponDecay(float decay)
{
    // TODO will set the weapong recharge value, near the reactor, recovers fast
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
    return sf::FloatRect(position().x, position().y, m_tileWidth, m_tileHeight);
    //return sf::FloatRect(position().x - m_tileWidth, position().y, m_tileWidth, m_tileHeight);
    //return sf::FloatRect(position().x, position().y, m_tileWidth, m_tileHeight);
    //return m_sprite.getGlobalBounds();

    //return m_sprite.getLocalBounds();
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
