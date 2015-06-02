#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character
{
public:
    Player(const std::string &fileName, int x, int y);
    ~Player();

    void setCollide(bool collide);
    void setWeaponDecay(float decay);

    void update(sf::Time delta = sf::Time::Zero);

    void handleEvent(const sf::Event &event);

private:
    void shoot(int x, int y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float m_weaponDecay;

    int m_maxNumBullets;
    int m_numBullets;

    float m_timeToIncBullet;
    float m_timeAccumulator;

    Sprite *m_bulletIndicator;

    bool m_moveRight;
    bool m_moveLeft;
    bool m_moveUp;
    bool m_moveDown;

    bool m_collide;
};

#endif // __PLAYER_H__
