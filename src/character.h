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
    Character (const std::string &fileName, int x, int y, bool mainChracter = false);
    ~Character();

    void shoot(int x, int y);
    void setWeaponDecay(float decay); // use only for Sheerin

    std::vector<Bullet *> bullets();
    void destroyBullet(Bullet *bullet);

    // enemy only function, track target
    void setTarget(std::vector<sf::Vector2f> waypoints, sf::Vector2f end);
    bool reactorHit();

    void freeze();
    bool deleteMe();

    sf::FloatRect boundingBox();
    // set if the sprite should collide or not (default = true)
    void setColliding(bool colliding);
    bool colliding();

    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);

    void setDirection(int x, int y);
    int directionX(); //

    void update(sf::Time delta = sf::Time::Zero);

    bool collideWith(Sprite *sprite);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updatePos(sf::Vector2f point);

    bool m_collidingEnabled;

    int m_tileWidth;
    int m_tileHeight;

    int m_xDirection;
    int m_yDirection;

    float m_weaponDecay;
    bool m_mainCharacter;

    int m_maxNumBullets;
    int m_numBullets;

    float m_timeToIncBullet;
    float m_timeAccumulator;

    std::vector<sf::Vector2f> m_target;
    int m_currentTarget;
    float m_step;
    bool m_reactorHit;
    bool m_freeze;

    bool m_deleteMe;
    float m_deleteTimeAccumulator;

    std::vector<Bullet *> m_bullets;
    Sprite *m_bulletIndicator;
};

#endif // __CHARACTER_H__
