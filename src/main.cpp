#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include <tmx/MapLoader.h>
#include <tmx/MapObject.h>

#include "character.h"

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 608), "ld32");
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // XXX move it to a common file

    // map loading
    tmx::MapLoader ml("resources/maps");
    ml.AddSearchPath("resources/tilesets");
    ml.Load("first.tmx");
    //

    sf::Vector2u mapSize = ml.GetMapSize();
    sf::Vector2u windowSize = window.getSize();

    sf::View view(sf::FloatRect(0, mapSize.y - windowSize.y, windowSize.x, windowSize.y));
    window.setView(view);

    Character *sheerin;
    std::vector<Character *> enemies;

    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto &l : layers) {
        if (l.name == "Characters") {
            for (const auto& o : l.objects) {
                if (o.GetName() == "Sheerin") {
                    sheerin = new Character("resources/sprites/chars.png", 0, 4);

                    sheerin->setPosition(o.GetPosition());
                    sheerin->setDirection(-1, 1);
                } else if (o.GetName() == "enemy1") {
                    Character *enemy = new Character("resources/sprites/chars.png", 0, 7);

                    enemy->setPosition(o.GetPosition());

                    enemies.push_back(enemy);
                } else if (o.GetName() == "enemy2") {
                    Character *enemy = new Character("resources/sprites/chars.png", 5, 1);

                    enemy->setPosition(o.GetPosition());
                    enemy->setDirection(-1, 1);

                    enemies.push_back(enemy);
                } else if (o.GetName() == "enemy3") {
                    Character *enemy = new Character("resources/sprites/chars.png", 1, 6);

                    enemy->setPosition(o.GetPosition());
                    enemy->setDirection(-1, 1);

                    enemies.push_back(enemy);
                }
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            //if (event.type == sf::Event::MouseMoved) {
                //if (event.mouseMove.x > sheerin->position().x)
                    //sheerin->setDirection(1, 1);
                //else if (event.mouseMove.x < sheerin->position().x)
                    //sheerin->setDirection(-1, 1);
            //}

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sheerin->shoot(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        float step = .3f;// TODO

        // keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sheerin->move(step, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sheerin->move(-step, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sheerin->move(0, -step);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sheerin->move(0, step);
        }

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

        window.clear(sf::Color(0, 0, 0));

        // update...
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
        }

        // TODO should go to an scene or layer
        sheerin->update(dt);
        for (auto &enemy : enemies)
            enemy->update(dt);

        window.draw(ml);
        window.draw(*sheerin);
        for (auto &enemy : enemies)
            window.draw(*enemy);

        window.display();
    }
}
