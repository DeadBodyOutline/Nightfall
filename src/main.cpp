#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include <tmx/MapLoader.h>
#include <tmx/MapObject.h>

#include "dronea.h"

using namespace std;

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ld32");
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // XXX move it to a common file

    sf::Vector2u windowSize = window.getSize();

    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    window.setView(view);

    // map loading
    tmx::MapLoader ml("resources/maps");
    ml.AddSearchPath("resources/tilesets");
    ml.AddSearchPath("resources/sprites");
    ml.Load("first.tmx");

    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();

    for (const auto& l : layers) {
        if (l.name == "Walls") {
            for (const auto& o : l.objects) {
                b2Body* b = tmx::BodyCreator::Add(o, world);

                debugBoxes.push_back(std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(6.f, 6.f))));
                sf::Vector2f pos = tmx::BoxToSfVec(b->GetPosition());
                debugBoxes.back()->setPosition(pos);
                debugBoxes.back()->setOrigin(3.f, 3.f);

                for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
                    b2Shape::Type shapeType = f->GetType();

                    if (shapeType == b2Shape::e_polygon) {
                        DebugShape ds;
                        ds.setPosition(pos);

                        b2PolygonShape* ps = (b2PolygonShape*)f->GetShape();
                        int count = ps->GetVertexCount();

                        for (int i = 0; i < count; i++)
                            ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(i)), sf::Color::Green));

                        ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(0)), sf::Color::Green));
                        debugShapes.push_back(ds);
                    }
                }
            }
        }
    }
    //

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

        window.display();
    }
}
