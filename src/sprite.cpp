#include <iostream>
#include <algorithm>
#include <cmath>

#include "sprite.h"

Sprite::Sprite(const std::string &fileName)
    : sf::Drawable()
    , m_width(0)
    , m_height(0)
    , m_visible(true)
{
    load(fileName);
    m_sprite.setOrigin(width() / 2, height() / 2);
}

Sprite::~Sprite()
{
}

void Sprite::setPosition(int x, int y)
{
    sf::Vector2f v(x, y);
    this->setPosition(v);
}

void Sprite::setPosition(sf::Vector2f point)
{
    if (point == m_sprite.getPosition())
        return;

    m_sprite.setPosition(point.x, point.y);
}

sf::Vector2f Sprite::position() const
{
    return m_sprite.getPosition();
}

void Sprite::setScale(float scaleX, float scaleY)
{
    // XXX should width() and height() return its values multiplied by scale?
    m_sprite.setScale(scaleX, scaleY);
}

int Sprite::width() const
{
    return m_width;
}

int Sprite::height() const
{
    return m_height;
}

void Sprite::setRotation(float angle)
{
    m_sprite.setRotation(angle);
}

float Sprite::rotation() const
{
    return m_sprite.getRotation();
}

void Sprite::setVisible(bool visible)
{
    if (visible == m_visible)
        return;

    m_visible = visible;
}

bool Sprite::visible() const
{
    return m_visible;
}

void Sprite::setTransparency(float value)
{

    int transparency = std::max(0.0, std::min(std::ceil(value * 255.0), 255.0));

    m_sprite.setColor(sf::Color(255, 255, 255, transparency));
}

void Sprite::update(sf::Time delta)
{
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_visible)
        return;

    target.draw(m_sprite);
}

bool Sprite::collideWith(Sprite *sprite)
{
    return m_sprite.getGlobalBounds().intersects(
            sprite->m_sprite.getGlobalBounds());
}

void Sprite::move(const float x, const float y)
{
    m_sprite.move(x, y);
}

bool Sprite::load(const std::string &fileName)
{
    m_texture = std::make_shared<sf::Texture>();

    if (!m_texture->loadFromFile(fileName)) {
        std::cout << "Fail loading '" << fileName << "'" << std::endl;
        return false;
    }

    m_width = m_texture->getSize().x;
    m_height = m_texture->getSize().y;

    m_sprite.setTexture(*m_texture);

    return true;
}
