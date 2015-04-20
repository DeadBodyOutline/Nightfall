#ifndef __REACTOR_H__
#define __REACTOR_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

#include "animatedsprite.h"

class Reactor : public AnimatedSprite
{
public:
    Reactor(const std::string &fileName, int x = 0, int y = 0);
    ~Reactor();

    int energyLevel();

    void update(sf::Time delta = sf::Time::Zero);

private:
    int m_energyLevel;

    int m_tileWidth;
    int m_tileHeight;
};

#endif // __REACTOR_H__
