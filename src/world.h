#ifndef __WORLD_H__
#define __WORLD_H__

#include <tmx/MapLoader.h>
//#include <SFML/Graphics.hpp>

#include "scene.h"

#include "player.h"
#include "reactor.h"

#include "layer.h"

class World : public Scene
{
public:
    World();
    ~World();

    void update(sf::Time delta = sf::Time::Zero);
    void handleEvent(const sf::Event &event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

private:
    tmx::MapLoader *m_mapLoader; // XXX shared_ptr?

    Player *m_sheerin;
    Reactor *m_reactor;

    sf::Vector2f m_newPos;

    Layer m_enemiesLayer;
    Layer m_mainLayer;

    float m_enemySpawnTimeAcc;

    std::vector<sf::Vector2f> m_spawnPoints;
    std::vector<std::vector<sf::Vector2f> > m_wayPoints;
};

#endif // __WORLD_H__
