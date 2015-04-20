#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

#include "animatedsprite.h"

class Bullet : public AnimatedSprite
{
public:
    Bullet(const std::string &fileName, int x = 0, int y = 0);
    ~Bullet();

    void run(float angle);
    void engage();

    void update(sf::Time delta = sf::Time::Zero);

private:
    float m_step;
    float m_angle;

    int m_tileWidth;
    int m_tileHeight;

    bool m_engaged;
};

#endif // __BULLET_H__
