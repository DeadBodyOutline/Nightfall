#ifndef __LAYER_H__
#define __LAYER_H__

#include <SFML/Graphics.hpp>

#include "sprite.h"

#include <map>

typedef std::vector<Sprite *> SpriteContainer;

class Layer : public sf::Drawable
{
public:
    Layer();
    virtual ~Layer();

    void addSprite(Sprite *sprite, int zOrder = 0);
    void remove(Sprite *sprite);

    // for manipulation
    SpriteContainer &sprites();

    void update(sf::Time delta = sf::Time::Zero);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    SpriteContainer m_sprites;
};

#endif // __LAYER_H__
