#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"

class Enemy : public Character
{
public:
    Enemy(const std::string &fileName, int x, int y);
    ~Enemy();

    void shoot(int x, int y);

    void setTarget(std::vector<sf::Vector2f> waypoints, sf::Vector2f end);
    bool reactorHit();

    void freeze();
    bool deleteMe();

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<sf::Vector2f> m_target;

    int m_currentTarget;
    bool m_reactorHit;
    bool m_freeze;

    bool m_deleteMe;
    float m_deleteTimeAccumulator;
};

#endif // __ENEMY_H__
