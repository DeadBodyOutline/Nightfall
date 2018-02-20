#include "world.h"

#include <tmx/MapObject.h>

#include <chrono>
#include <random>

#include "enemy.h"
#include "stuffmath.h"

World::World()
    : Scene()
    , m_sheerin(nullptr)
    , m_reactor(nullptr)
    , m_enemySpawnTimeAcc(0.f)
{
    // map loading
    m_mapLoader = new tmx::MapLoader("resources/maps");
    m_mapLoader->AddSearchPath("resources/tilesets");
    m_mapLoader->Load("first.tmx");
    sf::Vector2u mapSize = m_mapLoader->GetMapSize();
    //

    // special objects, including player
    //

    // spawn points from map
    //std::vector<sf::Vector2f> spawnPoints;
    //std::vector<std::vector<sf::Vector2f> > wayPoints;
    //

    //int enemiesIntoDarkness = 0;
    //bool gameOver = true;

    // Layers
    //Layer enemiesLayer;
    //Layer mainLayer; // layer to hold Player and Reactor;

    addLayer(m_enemiesLayer);
    addLayer(m_mainLayer);
    //

    // spawn accumulator
    //float enemySpawnTimeAcc = 0.f;

    // CONFIGURATION YET
    //const std::vector<tmx::MapLayer> &layers = m_mapLoader->GetLayers();
    //for (const auto &l : layers) {
    for (const auto &l : m_mapLoader->GetLayers()) {
        if (l.name == "characters") {
            for (const auto& o : l.objects) {
                if (o.GetName() == "Sheerin") {
                    m_sheerin = new Player("resources/sprites/chars.png", 0, 36);

                    m_sheerin->setPosition(o.GetPosition());
                    m_sheerin->setDirection(-1, 1);

                   m_mainLayer.addSprite(*m_sheerin);
                } else if (o.GetName() == "enemy1")
                    m_spawnPoints.push_back(o.GetPosition());
                else if (o.GetName() == "enemy2")
                    m_spawnPoints.push_back(o.GetPosition());
                else if (o.GetName() == "enemy3")
                    m_spawnPoints.push_back(o.GetPosition());
            }
        }

        // insert 'shrug' here
        if (l.name == "waypoints") {
            for (const auto& o : l.objects) {
                if (o.GetName() == "waypoint1") {
                    if (m_wayPoints.size() == 0) {
                        std::vector<sf::Vector2f> v;
                        v.push_back(o.GetPosition());

                        m_wayPoints.push_back(v);
                    } else
                        m_wayPoints[0].push_back(o.GetPosition());
                } else if (o.GetName() == "waypoint2") {
                    if (m_wayPoints.size() == 1) {
                        std::vector<sf::Vector2f> v;
                        v.push_back(o.GetPosition());

                        m_wayPoints.push_back(v);
                    } else
                        m_wayPoints[1].push_back(o.GetPosition());
                } else if (o.GetName() == "waypoint3") {
                    if (m_wayPoints.size() == 2) {
                        std::vector<sf::Vector2f> v;
                        v.push_back(o.GetPosition());

                        m_wayPoints.push_back(v);
                    } else
                        m_wayPoints[2].push_back(o.GetPosition());
                }
            }
        }

        if (l.name == "objects") {
            for (const auto &o : l.objects) {
                if (o.GetName() == "reactor") {
                    m_reactor = new Reactor("resources/sprites/reactor.png");
                    // offset to properly collide withreacotr
                    m_reactor->setPosition(o.GetPosition() - sf::Vector2f(0, 32));

                    m_mainLayer.addSprite(*m_reactor);
                }
            }
        }
    }
    //
}

World::~World()
{
}

void World::update(sf::Time delta)
{
    // TODO update view
    // //TODO destroy enemies/bullets

    // TODO object updates

    // TODO collisions

    checkCollisions();

    // TODO destroy things (remove killed enemies, etc...)
    // TODO spawn enemies
    // TODO update positioning (outside view, collisions?)
    //

    // XXX mechanism to tell Game to finish world
    //if (m_reactor->energyLevel() <= 0) {
        //gameOver = true;
    //}


    // adjust the player's weapon decay
    calculateWeaponDecay();

    // check if it's time to spawn a new enemy
    m_enemySpawnTimeAcc += delta.asSeconds();
    if (m_enemySpawnTimeAcc >= 2.f) {
        spawnEnemies();
        m_enemySpawnTimeAcc = 0.f;
    }

    // finally update scene child object
    Scene::update(delta);
}

void World::handleEvent(const sf::Event &event)
{
    m_sheerin->handleEvent(event);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*m_mapLoader);

    Scene::draw(target, states);
}

void World::checkCollisions()
{
    m_mapLoader->UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800, 608));
    //m_mapLoader->UpdateQuadTree(sf::FloatRect(m_sheerin->position().x - 16, m_sheerin->position().y, 32, 32));
    sf::FloatRect tR = m_sheerin->boundingBox();
    std::vector<tmx::MapObject*> objects = m_mapLoader->QueryQuadTree(tR);

    bool collide = false;
    for (auto &o : objects) {
            if (o->GetName() == "reactor")
                collide = true;

            if (o->GetName() == "block")
                collide = true;

            if (o->GetName() == "wall")
                collide = true;
    }
    // TODO adjust
    m_sheerin->setCollide(collide);

    // bullet collision with blocks
    // TODO adjust
    auto &objectsObjects = m_mapLoader->GetLayers()[3].objects;
    for (auto &o : objectsObjects) {
        for (auto &bullet : m_sheerin->bullets()) {
            sf::Vector2f bPos = bullet->position() + sf::Vector2f(32, 32);
            if (o.Contains(bPos)) {
                m_sheerin->destroyBullet(bullet);
                break;
            }
        }
    }

    // bullet collision with enemies
    // TODO adjust
    for (auto &sprite : m_enemiesLayer.sprites()) {
        for (auto &bullet : m_sheerin->bullets()) {
            if (!bullet->engaged()) {
                sf::Vector2f bPos = bullet->position() + sf::Vector2f(32, 32);
                Enemy *enemy = dynamic_cast<Enemy *>(sprite);

                if (enemy->colliding() && bullet->collideWith(enemy)) {
                    enemy->setColliding(false);

                    int direction = enemy->directionX();
                    bullet->engage(enemy->position() - sf::Vector2f(direction == 1 ? 16 : 32, 16));
                    enemy->freeze();

                    //enemiesIntoDarkness++; // XXX
                }
            } else if (bullet->deleteMe()) {
                m_sheerin->destroyBullet(bullet);
            }
        }

        Enemy *enemy = dynamic_cast<Enemy *>(sprite);

        if (enemy->reactorHit()) {
            m_reactor->takeDamage(6); // TODO

            m_enemiesLayer.remove(*sprite);
        } else if (enemy->deleteMe())
            m_enemiesLayer.remove(*sprite);
    }
}

void World::calculateWeaponDecay()
{
    sf::Vector2f sPos(m_sheerin->position().x, m_sheerin->position().y);
    sf::Vector2f rPos(m_reactor->position().x, m_reactor->position().y);

    // shitty approximation, but it works (:thumbs up:)
    float d = -1.f;
    if (sPos.x >= rPos.x)
        rPos.x += 96;
    if (sPos.y >= rPos.y)
        rPos.y += 96;

    d = stuffDistanceF(sPos.x, sPos.y, rPos.x, rPos.y);

    if (d > 135)
        m_sheerin->setWeaponDecay(d / 100);
    else
        m_sheerin->setWeaponDecay(1.f);
}

void World::spawnEnemies()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distr(0, m_spawnPoints.size() - 1);
    int p = distr(gen);

    distr = std::uniform_int_distribution<int>(0, 69); // 70 different characters
    int character;

    // avoid spawning Sheerin (char #36)
    do {
        character = distr(gen);
    } while (character == 36);

    Enemy *enemy = new Enemy("resources/sprites/chars.png", 0, character);
    sf::Vector2f spawnPoint = m_spawnPoints[p];

    enemy->setPosition(spawnPoint);
    if (spawnPoint.x > m_reactor->position().x)
        enemy->setDirection(-1, 1);

    enemy->setTarget(m_wayPoints[p], m_reactor->position());
    m_enemiesLayer.addSprite(*enemy);
}
