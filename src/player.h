#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character
{
public:
    Player(const std::string &fileName, int x, int y);
    ~Player();

    void shoot(int x, int y);
    void setWeaponDecay(float decay);

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float m_weaponDecay;

    int m_maxNumBullets;
    int m_numBullets;

    float m_timeToIncBullet;
    float m_timeAccumulator;

    Sprite *m_bulletIndicator;
};

#endif // __PLAYER_H__
