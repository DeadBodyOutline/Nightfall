#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <tmx/MapObject.h>

#include <string>

#include "animatedsprite.h"

class Character : public AnimatedSprite
{
public:
    Character(const std::string &fileName, int x, int y);
    ~Character();

    // set if the sprite should collide or not (default = true)
    void setColliding(bool colliding);
    bool colliding();

    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);

    void setDirection(int x, int y);

    void update(sf::Time delta = sf::Time::Zero);

    bool collideWith(Sprite *sprite);

private:
    void updatePos(sf::Vector2f point);

    bool m_collidingEnabled;

    int m_tileWidth;
    int m_tileHeight;

    int m_xOffset;
    int m_yOffset;

    int m_xDirection;
    int m_yDirection;
};

#endif // __CHARACTER_H__
