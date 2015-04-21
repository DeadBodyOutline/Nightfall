#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

#include "animatedsprite.h"
#include "eyes.h"

class Bullet : public AnimatedSprite
{
public:
    Bullet(const std::string &fileName, int x = 0, int y = 0);
    ~Bullet();

    void run(float angle);
    void engage(sf::Vector2f pos);
    bool engaged();

    bool deleteMe();

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float m_step;
    float m_angle;

    int m_tileWidth;
    int m_tileHeight;

    bool m_engaged;
    bool m_deleteMe;

    float m_deleteTimeAccumulator;

    Eyes *m_eyes;
};

#endif // __BULLET_H__
