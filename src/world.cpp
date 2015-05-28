#include "world.h"

#include <tmx/MapLoader.h>
#include <tmx/MapObject.h>

#include "player.h"
#include "reactor.h"

World::World()
    : Scene()
{
    // map loading
    tmx::MapLoader ml("resources/maps");
    ml.AddSearchPath("resources/tilesets");
    ml.Load("first.tmx");
    sf::Vector2u mapSize = ml.GetMapSize();
    //

    // special objects, including player
    Player *sheerin;
    Reactor *reactor;
    //

    // spawn points from map
    std::vector<sf::Vector2f> spawnPoints;
    std::vector<std::vector<sf::Vector2f> > wayPoints;
    //

    int enemiesIntoDarkness = 0;
    bool gameOver = true;

    // Layers
    Layer enemiesLayer;
    Layer mainLayer; // layer to hold Player and Reactor;

    addLayer(enemiesLayer);
    addLayer(mainLayer);
    //

    // spawn accumulator
    float enemySpawnTimeAcc = 0.f;

    // CONFIGURATION YET
    //const std::vector<tmx::MapLayer> &layers = ml.GetLayers();
    //for (const auto &l : layers) {
    for (const auto &l : ml.GetLayers()) {
        if (l.name == "characters") {
            for (const auto& o : l.objects) {
                if (o.GetName() == "Sheerin") {
                    sheerin = new Player("resources/sprites/chars.png", 0, 36);

                    sheerin->setPosition(o.GetPosition());
                    sheerin->setDirection(-1, 1);

                    mainLayer.addSprite(*sheerin);
                } else if (o.GetName() == "enemy1")
                    spawnPoints.push_back(o.GetPosition());
                else if (o.GetName() == "enemy2")
                    spawnPoints.push_back(o.GetPosition());
                else if (o.GetName() == "enemy3")
                    spawnPoints.push_back(o.GetPosition());
            }
        }

        // insert 'shrug' here
        if (l.name == "waypoints") {
            for (const auto& o : l.objects) {
                if (o.GetName() == "waypoint1") {
                    if (wayPoints.size() == 0) {
                        std::vector<sf::Vector2f> v;
                        v.push_back(o.GetPosition());

                        wayPoints.push_back(v);
                    } else
                        wayPoints[0].push_back(o.GetPosition());
                } else if (o.GetName() == "waypoint2") {
                    if (wayPoints.size() == 1) {
                        std::vector<sf::Vector2f> v;
                        v.push_back(o.GetPosition());

                        wayPoints.push_back(v);
                    } else
                        wayPoints[1].push_back(o.GetPosition());
                } else if (o.GetName() == "waypoint3") {
                    if (wayPoints.size() == 2) {
                        std::vector<sf::Vector2f> v;
                        v.push_back(o.GetPosition());

                        wayPoints.push_back(v);
                    } else
                        wayPoints[2].push_back(o.GetPosition());
                }
            }
        }

        if (l.name == "objects") {
            for (const auto &o : l.objects) {
                if (o.GetName() == "reactor") {
                    reactor = new Reactor("resources/sprites/reactor.png");
                    // offset to properly collide withreacotr
                    reactor->setPosition(o.GetPosition() - sf::Vector2f(0, 32));

                    mainLayer.addSprite(*reactor);
                }
            }
        }
    }
    //
}

World::~World()
{
}
