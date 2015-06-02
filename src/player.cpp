#include "player.h"

Player::Player(const std::string &fileName, int x, int y)
    : Character(fileName, x, y)
    , m_weaponDecay(1.f)
    , m_maxNumBullets(10) // TODO 10
    , m_numBullets(m_maxNumBullets)
    , m_timeToIncBullet(2.f)
    , m_timeAccumulator(0.f)
    , m_moveRight(false)
    , m_moveLeft(false)
    , m_moveUp(false)
    , m_moveDown(false)
    , m_collide(false)
{
    m_bulletIndicator = new Sprite("resources/sprites/bullet_indicator.png");
    m_step = 100.f;
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

void Player::setCollide(bool collide)
{
    m_collide = collide;
}

void Player::update(sf::Time delta)
{
    m_timeAccumulator += delta.asSeconds() * (1.f / m_weaponDecay);
    if (m_timeAccumulator >= m_timeToIncBullet) {
        if (m_numBullets < m_maxNumBullets)
            ++m_numBullets;

        m_timeAccumulator = 0.f;
    }

    if (!m_collide) {
        sf::Vector2f newPos(0.f, 0.f);
        if (m_moveLeft)
            newPos.x -= m_step;

        if (m_moveRight)
            newPos.x += m_step;

        if (m_moveUp)
            newPos.y -= m_step;

        if (m_moveDown)
            newPos.y += m_step;

        newPos *= delta.asSeconds();
        move(newPos.x, newPos.y);
    }

    Character::update(delta);
}

void Player::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        if (event.mouseMove.x > position().x)
            setDirection(1, 1);
        else if (event.mouseMove.x < position().x)
            setDirection(-1, 1);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            //sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            //sheerin->shoot(mousePos.x, mousePos.y);
            shoot(event.mouseButton.x, event.mouseButton.y);
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::D)
            m_moveRight = true;

        if (event.key.code == sf::Keyboard::A)
            m_moveLeft = true;

        if (event.key.code == sf::Keyboard::W)
            m_moveUp = true;

        if (event.key.code == sf::Keyboard::S)
            m_moveDown = true;
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::D)
            m_moveRight = false;

        if (event.key.code == sf::Keyboard::A)
            m_moveLeft = false;

        if (event.key.code == sf::Keyboard::W)
            m_moveUp = false;

        if (event.key.code == sf::Keyboard::S)
            m_moveDown = false;
    }
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
