#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <tmx/MapObject.h>

#include <string>

#include "animatedsprite.h"
#include "bullet.h"

class Character : public AnimatedSprite
{
public:
    Character(const std::string &fileName, int x, int y);
    ~Character();

    void shoot(int x, int y);

    std::vector<Bullet *> bullets();
    void destroyBullet(Bullet *bullet);

    sf::FloatRect boundingBox();

    void setColliding(bool colliding);
    bool colliding();

    // XXX Sprite/AnimatedSprite doesn't do it already?
    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);

    void setDirection(int x, int y);
    int directionX(); //

    void update(sf::Time delta = sf::Time::Zero);

    bool collideWith(Sprite *sprite);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Bullet *> m_bullets;

    int m_xDirection;
    int m_yDirection;

    float m_step;

private:
    void updatePos(sf::Vector2f point);

    bool m_collidingEnabled;

    int m_tileWidth;
    int m_tileHeight;
};

#endif // __CHARACTER_H__
