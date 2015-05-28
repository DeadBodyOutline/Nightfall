#include <chrono>
#include <random>

#include "game.h"
#include "world.h"

#include "enemy.h"
#include "bullet.h"

// XXX game should contain Scenes handling, update and input.
// All game related things should live at some scene
Game::Game(int width, int height, const std::string &title)
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height),
            title);

    m_windowSize = m_window->getSize();

    m_window->setKeyRepeatEnabled(false);
    m_window->setVerticalSyncEnabled(true);

    // game world, really it's just a scene
    World *world = new World();
    m_scenes.push_back(world);
}

Game::~Game()
{
    m_scenes.clear();
}

int Game::excelsior()
{
    // view setup
    sf::View view = sf::View(sf::FloatRect(0, mapSize.y - m_windowSize.y,
                m_windowSize.x, m_windowSize.y));
    m_window->setView(view);
    //


    // Game scene
    //Scene scene;

    // timing
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // XXX move it to a common file
    sf::Clock clock;

    // LOOP
    while (m_window->isOpen()) {
        sf::Event event;

        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window->close();

            if (event.key.code == sf::Keyboard::Escape)
                m_window->close();

            if (event.type == sf::Event::MouseMoved) {
                if (event.mouseMove.x > sheerin->position().x)
                    sheerin->setDirection(1, 1);
                else if (event.mouseMove.x < sheerin->position().x)
                    sheerin->setDirection(-1, 1);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    //sheerin->shoot(mousePos.x, mousePos.y);
                    sheerin->shoot(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        float step = .1f;// TODO

        sf::Vector2f newPos(0, 0);
        // keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            newPos.x += step;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            newPos.x += -step;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            newPos.y += -step;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            newPos.y += step;
        }

        // TODO hum
        ml.UpdateQuadTree(sf::FloatRect(sheerin->position().x + newPos.x - 16, sheerin->position().y + newPos.y, 32, 32));
        sf::FloatRect tR = sheerin->boundingBox();
        std::vector<tmx::MapObject*> objects = ml.QueryQuadTree(tR);

        bool collide = false;
        for (auto &o : objects) {
                if (o->GetName() == "reactor")
                    collide = true;

                if (o->GetName() == "block")
                    collide = true;

                if (o->GetName() == "wall")
                    collide = true;
        }

        if (!collide) {
            sheerin->move(newPos.x, newPos.y);
        }

        // bullet collision with blocks
        // TODO adjust
        auto &objectsObjects = ml.GetLayers()[3].objects;
        for (auto &o : objectsObjects) {
            for (auto &bullet : sheerin->bullets()) {
                sf::Vector2f bPos = bullet->position() + sf::Vector2f(32, 32);
                if (o.Contains(bPos)) {
                    sheerin->destroyBullet(bullet);
                    break;
                }
            }
        }

        // bullet collision with enemies
        // TODO adjust
        for (auto &sprite : enemiesLayer.sprites()) {
            for (auto &bullet : sheerin->bullets()) {
                if (!bullet->engaged()) {
                    sf::Vector2f bPos = bullet->position() + sf::Vector2f(32, 32);
                    Enemy *enemy = dynamic_cast<Enemy *>(sprite);

                    if (enemy->colliding() && bullet->collideWith(enemy)) {
                        enemy->setColliding(false);

                        int direction = enemy->directionX();
                        bullet->engage(enemy->position() - sf::Vector2f(direction == 1 ? 16 : 32, 16));
                        enemy->freeze();

                        enemiesIntoDarkness++;
                    }
                } else if (bullet->deleteMe()) {
                    sheerin->destroyBullet(bullet);
                }
            }

            Enemy *enemy = dynamic_cast<Enemy *>(sprite);

            if (enemy->reactorHit()) {
                reactor->takeDamage(6); // TODO

                enemiesLayer.remove(*sprite);
            } else if (enemy->deleteMe())
                enemiesLayer.remove(*sprite);
        }

        if (reactor->energyLevel() <= 0) {
            gameOver = true;
        }

        sf::Vector2f sPos(sheerin->position().x, sheerin->position().y);
        sf::Vector2f rPos(reactor->position().x, reactor->position().y);

        // shitty approximation, but it works (:thumbs up:)
        float d = -1.f;
        if (sPos.x >= rPos.x)
            rPos.x += 96;
        if (sPos.y >= rPos.y)
            rPos.y += 96;

        d = stuffDistanceF(sPos.x, sPos.y, rPos.x, rPos.y);

        if (d > 135)
            sheerin->setWeaponDecay(d / 100);
        else
            sheerin->setWeaponDecay(1.f);
        //

        // mouse input
        // TODO check difference of doing it or inside event
        //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //if (mousePos.x > sheerin->position().x)
            //sheerin->setDirection(1, 1);
        //else if (mousePos.x < sheerin->position().x)
            //sheerin->setDirection(-1, 1);

        // TODO this give a lot of shoot, moving to inside event
        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //std::cout << "SHOOT!" << std::endl;
        //}

        m_window->clear(sf::Color(0, 0, 0));

        // update...
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            //scene.update(TimePerFrame);
        }

        // spawn new enemies each 2 seconds
        enemySpawnTimeAcc += dt.asSeconds();
        if (enemySpawnTimeAcc >= 2.f) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine gen(seed);
            std::uniform_int_distribution<int> distr(0, spawnPoints.size() - 1);
            int p = distr(gen);

            distr = std::uniform_int_distribution<int>(0, 69); // 70 different characters
            int character;

            // avoid spawning Sheerin (char #36)
            do {
                character = distr(gen);
            } while (character == 36);

            Enemy *enemy = new Enemy("resources/sprites/chars.png", 0, character);
            sf::Vector2f spawnPoint = spawnPoints[p];

            enemy->setPosition(spawnPoint);
            if (spawnPoint.x > reactor->position().x)
                enemy->setDirection(-1, 1);

            enemy->setTarget(wayPoints[p], reactor->position());
            enemiesLayer.addSprite(*enemy);

            enemySpawnTimeAcc = 0.f;
        }

        scene.update(dt);

        m_window->draw(ml);
        m_window->draw(scene);

        m_window->display();
    }

    return 0;
}

void Game::draw()
{
    // TODO
}
