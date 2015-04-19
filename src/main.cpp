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

    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto &l : layers) {
        if (l.name == "Characters") {
            for (const auto& o : l.objects) {
                if (o.GetName() == "Sheerin") { // all terrain
                    sheerin = new Character("resources/sprites/chars.png", 0, 4);
                    sheerin->setPosition(o.GetPosition());
                }
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color(0, 0, 0));

        // update...
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
        }

        // TODO should go to an scene or layer
        sheerin->update(dt);

        window.draw(ml);
        window.draw(*sheerin);

        window.display();
    }
}
