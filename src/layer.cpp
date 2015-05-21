#include "layer.h"

// XXX move to an utils file
#define UNUSED(x) (void)x;

Layer::Layer()
    : sf::Drawable()
{
}

Layer::~Layer()
{
    m_sprites.clear();
}

void Layer::addSprite(Sprite &sprite, int zOrder)
{
    UNUSED(zOrder); // one day it will be used, one day...
    m_sprites.push_back(&sprite);
}

void Layer::remove(Sprite &sprite)
{
    m_sprites.erase(
            std::remove(m_sprites.begin(), m_sprites.end(), &sprite),
            m_sprites.end());

    delete &sprite;
}

SpriteContainer &Layer::sprites()
{
    return m_sprites;
}

void Layer::update(sf::Time delta)
{
    for (auto sprite : m_sprites)
        sprite->update(delta);
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto sprite : m_sprites)
        target.draw(*sprite);
}
