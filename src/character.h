#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <tmx/MapObject.h>

#include <string>

#include "sprite.h"

class Character : public Sprite
{
public:
    Character(const std::string &fileName);
    //Character(const tmx::MapObject &object);
    //Character(const tmx::MapObject &object, const std::string &fileName, b2World *world = nullptr);
    ~Character();

    //virtual void moveToPosition(sf::Vector2f point) = 0;

    // set if the sprite should collide or not (default = true)
    void setColliding(bool colliding);
    bool colliding();

    void update(sf::Time delta = sf::Time::Zero);
    //void draw(sf::RenderTarget &target);

    bool collideWith(Sprite *sprite);

protected:
    bool m_collidingEnabled;
};

#endif // __CHARACTER_H__
