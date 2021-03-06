#include "character.h"

Character::Character(const std::string &fileName, int x, int y, bool mainCharacter)
    : AnimatedSprite(fileName, 32, 2304)
    , m_collidingEnabled(true)
    , m_tileWidth(32)
    , m_tileHeight(32)
    , m_xDirection(1)
    , m_yDirection(1)
    , m_weaponDecay(1.f)
    , m_mainCharacter(mainCharacter)
    , m_maxNumBullets(10) // TODO 10
    , m_numBullets(m_maxNumBullets)
    , m_timeToIncBullet(2.f)
    , m_timeAccumulator(0.f)
    , m_currentTarget(0)
    , m_step(m_mainCharacter ? 0.1f : 0.05f)
    , m_reactorHit(false)
    , m_freeze(false)
    , m_deleteMe(false)
    , m_deleteTimeAccumulator(0.f)
{
    m_bulletIndicator = new Sprite("resources/sprites/bullet_indicator.png");

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
    if (m_numBullets <= 0)
        return;

    sf::Vector2f posCorrection = sf::Vector2f(32, 16); // XXX I don't know why, but will discover someday

    Bullet *bullet = new Bullet("resources/sprites/darkbullet.png");

    sf::Vector2f v = sf::Vector2f(x - 32, y - 32) - (position() - posCorrection);
    float angle = atan2f(v.y, v.x);

    bullet->run(angle);
    bullet->setPosition(position() - posCorrection);

    m_bullets.push_back(bullet);

    --m_numBullets;
}
void Character::setWeaponDecay(float decay)
{
    // TODO will set the weapong recharge value, near the reactor, recovers fast
    m_weaponDecay = decay;
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

// enemy only function, track target
void Character::setTarget(std::vector<sf::Vector2f> waypoints, sf::Vector2f end)
{
    m_target = waypoints;
    m_target.push_back(end);
}

bool Character::reactorHit()
{
    return m_reactorHit;
}

void Character::freeze()
{
    m_freeze = true;
    // TODO freeze state
}

bool Character::deleteMe()
{
    return m_deleteMe;
}

sf::FloatRect Character::boundingBox()
{
    // XXX seems to do nothing oO
    return sf::FloatRect(position().x, position().y, m_tileWidth, m_tileHeight);
    //return sf::FloatRect(position().x + m_tileWidth, position().y, m_tileWidth, m_tileHeight);
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

    sf::IntRect r = m_sprite.getTextureRect();

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
    if (m_freeze) {
        m_deleteTimeAccumulator += delta.asSeconds();

        if (m_deleteTimeAccumulator >= 8) {
            m_deleteMe = true;

            m_deleteTimeAccumulator = 0.f;
        }

        for (auto bullet : m_bullets)
            bullet->update(delta);

        AnimatedSprite::update(delta);
        return;
    }

    // XXX use "contains" or something like that
    for (auto bullet : m_bullets) {
        if (bullet->position().x + 32 < 0 || bullet->position().y + 32 < 0  ||
                bullet->position().x > 800 || bullet->position().y > 608)
            destroyBullet(bullet);
        else
            bullet->update(delta);
    }

    if (m_mainCharacter) {
        //std::cout << "Recharging: " << 1.f / m_weaponDecay << std::endl;
        //std::cout << "Bullets: " << m_numBullets << std::endl;

        m_timeAccumulator += delta.asSeconds() * (1.f / m_weaponDecay);
        if (m_timeAccumulator >= m_timeToIncBullet) {
            if (m_numBullets < m_maxNumBullets)
                ++m_numBullets;

            m_timeAccumulator = 0.f;
        }

        //std::cout << "time: " << m_timeAccumulator << std::endl;
        //std::cout << "--" << std::endl;
    } else {
        float x = (m_xDirection == 1 ? 0 : 32);
        int diff = 2;

        if (m_currentTarget == m_target.size() -1) {
            if (m_xDirection == -1)
                diff = 96;
            else
                diff = 32;
        }

        //std::cout << "Pos: " << position().x << ", " << position().y << std::endl;
        //std::cout << "Tar: " << m_target[m_currentTarget].x << ", " << m_target[m_currentTarget].y << std::endl;
        //std::cout << "Cur: " << m_currentTarget << std::endl;
        //std::cout << "Dif: " << fabs(x + position().x - m_target[m_currentTarget].x) << std::endl;
        //std::cout << "Siz: " << m_target.size() << std::endl;

        if (fabs(x + position().x - m_target[m_currentTarget].x) <= 2 + x + diff) {
            m_currentTarget++;

            if (m_currentTarget >= m_target.size())
                m_reactorHit = true;
        }

        if (!m_reactorHit) {
            sf::Vector2f posCorrection = sf::Vector2f(0, 0); // damn
            if (m_currentTarget == m_target.size() -1)
                posCorrection = sf::Vector2f(m_xDirection == 1 ? 32 : 96, 48);

            sf::Vector2f v = sf::Vector2f(
                    m_target[m_currentTarget].x, m_target[m_currentTarget].y)
                    + posCorrection - position();

            float angle = atan2f(v.y, v.x);

            float newX = cos(angle) * m_step;
            float newY = sin(angle) * m_step;

            move(newX, newY);
        }
    }

    AnimatedSprite::update(delta);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_freeze) {
        for (auto bullet : m_bullets)
            target.draw(*bullet, states);

        return;
    }

    if (!m_visible)
        return;

    for (auto bullet : m_bullets)
        target.draw(*bullet, states);

    if (m_mainCharacter) {
        int x = position().x - 16;
        int y = position().y - 8;

        int i;
        for (i = 0; i < m_numBullets; i++) {
            m_bulletIndicator->setPosition(x, y);
            target.draw(*m_bulletIndicator);

            x += 1 + m_bulletIndicator->width();
        }
    }

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
